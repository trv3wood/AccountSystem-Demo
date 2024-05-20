#include "basicAccount.h"

#include <gmpxx.h>

#include <QString>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Encryptable/Encryptable.h"
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
}

void BasicAccount::serialize(QFile& file) const {
    // if (!file.open(QIODevice::WriteOnly)) {
    //     std::cerr << "Cannot open file for writing" << std::endl;
    //     return;
    // }
    QDataStream ds;
    ds.setDevice(&file);
    ds.setVersion(QDataStream::Qt_5_15);
    ds << name() << passwd() << location() << id() << cardNumber()
    << mpf_class2str(m_balance) << mpf_class2str(m_interestRate);
    // file.close();
}

void BasicAccount::deserialize(QFile& file) {
    QDataStream ids;
    // if (!file.exists()) {
    //     std::cerr << "File does not exist." << std::endl;
    //     return;
    // }
    ids.setDevice(&file);
    ids.setVersion(QDataStream::Qt_5_15);
    QString name, passwd, location, id, cardNumber, balance, interestRate;
    ids >> name >> passwd >> location >> id >> cardNumber >> balance >> interestRate;
    m_name = name.toStdString();
    m_passwd = passwd.toStdString();
    m_location = location.toStdString();
    m_id = id.toStdString();
    m_cardNumber = cardNumber.toStdString();
    m_balance = balance.toStdString();
    m_interestRate = interestRate.toStdString();
    // file.close();
}

void BasicAccount::setPasswd(const std::string& passwd) {
    m_passwd = preEncrypt(hashSHA256(passwd));
}

BasicAccount::BasicAccount(const std::string& name, const std::string& passwd,
             const std::string& location, const std::string& id)
    : Account(name, passwd, location, id) {
    m_balance = 0;
    m_interestRate = defualtInterestRate;
    m_datafile = m_name + ".dat";
}

void BasicAccount::decrypt() {
    m_name = preDecrypt(m_name);
    m_passwd = preDecrypt(m_passwd);
    m_location = preDecrypt(m_location);
    m_id = preDecrypt(m_id);
    m_cardNumber = preDecrypt(m_cardNumber);
}

void BasicAccount::encrypt() {
    m_name = preEncrypt(m_name);
    m_passwd = preEncrypt(m_passwd);
    m_location = preEncrypt(m_location);
    m_id = preEncrypt(m_id);
    m_cardNumber = preEncrypt(m_cardNumber);
}

void BasicAccount::store() {
    encrypt();
    QFile file(m_datafile.c_str());
    serialize(file);
    file.close();
}

void BasicAccount::load(QFile& file) {
    deserialize(file);
    decrypt();
    file.close();
}

}  // namespace bms