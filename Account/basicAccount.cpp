#include "basicAccount.h"

#include <gmpxx.h>

#include <QString>
#include <cstdlib>
#include <iostream>
#include <utility>

#include "Serializable/Serializable.h"
#include "account.h"


namespace bms {
const unsigned BasicAccount::transferRestriction = 5000;

void BasicAccount::transfer(Account* to, const mpf_class& amount) {
    if (amount > transferRestriction) {
        std::cerr << "Transfer amount exceeds the restriction." << '\n';
        return;
    }
    Account::transfer(to, amount);
    QFile file(to->datafile());
    dynamic_cast<BasicAccount*>(to)->serialize(file);
    file.close();
}

void BasicAccount::serialize(QFile& file) const {
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for writing" << std::endl;
        return;
    }
    QDataStream ds;
    ds.setDevice(&file);
    ds.setVersion(QDataStream::Qt_5_15);
    basicSerialize(ds, file);
    ds << mpf_class2str(m_balance) << mpf_class2str(m_interestRate);
    file.close();
}

void BasicAccount::deserialize(QFile& file) {
    QDataStream ids;
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Failed to open file for reading");
    }
    ids.setDevice(&file);
    ids.setVersion(QDataStream::Qt_5_15);
    QString balance, interestRate;
    basicDeserialize(ids, file);
    ids >> balance >> interestRate;
    m_balance = balance.toStdString();
    m_interestRate = interestRate.toStdString();
    file.close();
}

void BasicAccount::deposit(const mpf_class& amount) {
    Account::deposit(amount);
    QFile file(datafile());
    serialize(file);
    file.close();
}

void BasicAccount::setPasswd(const QString& passwd) {
    m_passwd = hashSHA256(passwd);
    QFile file(datafile());
    serialize(file);
    file.close();
}

BasicAccount::BasicAccount(QString name, QString passwd, QString location,
                           QString id)
    : Account(std::move(name), std::move(passwd), std::move(location),
              std::move(id)) {
    QFile file(datafile());
    serialize(file);
    file.close();
}

QString BasicAccount::predecrypt(const QString& plaintext) {
    // Convert QString to QByteArray
    QByteArray plaintextData = plaintext.toUtf8();

    // Convert QByteArray to unsigned char*
    unsigned char* plaintextPtr = reinterpret_cast<unsigned char*>(plaintextData.data());

    // Calculate the length of the plaintext
    int plaintextLen = plaintextData.size();

    // Call the base class's encryptImpl method
    unsigned char ciphertext[1024]; // Assuming maximum size
    int ciphertextLen = decryptImpl(plaintextPtr, plaintextLen, Encryptable::key, Encryptable::iv, ciphertext);

    // Convert the ciphertext to QString
    QString encryptedText = QString::fromUtf8(reinterpret_cast<const char*>(ciphertext), ciphertextLen);

    return encryptedText;
}

void BasicAccount::decrypt() {
    m_name = predecrypt(m_name);
    m_passwd = predecrypt(m_passwd);
    m_location = predecrypt(m_location);
    m_id = predecrypt(m_id);
    m_cardNumber = predecrypt(m_cardNumber);
}
}  // namespace bms