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
}  // namespace bms