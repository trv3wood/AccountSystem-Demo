#include "account.h"

#include <gmpxx.h>
#include <openssl/sha.h>

#include <QString>
#include <sstream>
#include <stdexcept>
#include <string>

#if ACCOUNT_DEBUG == 1
#include <cassert>
#endif

using bms::Account;

QString Account::name() const { return m_name; }

QString Account::passwd() const { return m_passwd; }

QString Account::location() const { return m_location; }

QString Account::id() const { return m_id; }

void Account::setName(const QString& name) { m_name = name; }

void Account::setPasswd(const QString& passwd) {
    m_passwd = hashSHA256(passwd);
}

void Account::setLocation(const QString& location) { m_location = location; }

void Account::setId(const QString& id) { m_id = id; }

void Account::setInterestRate(double rate) { m_interestRate = rate; }

void Account::transfer(Account& to, mpf_class amount) {
    if (m_balance >= amount) {
        m_balance -= amount;
        to.m_balance += amount;
        QDateTime currentTime = QDateTime::currentDateTime();
        m_time = currentTime.toString("yyyy-MM-dd hh:mm:ss");
#if ACCOUNT_DEBUG == 1
        qDebug() << "Transfer successful!";
#endif
    } else {
        std::stringstream msg;
        msg << "Transfer failed! " << m_name.toStdString()
            << " has not enough money!\n"
            << " Current balance: " << m_balance << " Amount: " << amount;
        throw std::runtime_error(msg.str());
    }
}

QString Account::hashSHA256(const QString& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];  // 32 字节的哈希值
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.toStdString().c_str(), str.length());
    SHA256_Final(hash, &sha256);
    char hex[2 * SHA256_DIGEST_LENGTH + 1];  // 64 字节的十六进制字符串
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex + 2 * i, "%02x", hash[i]);  // 两个字符表示一个字节
    }
    hex[2 * SHA256_DIGEST_LENGTH] = 0;  // 字符串结尾
    return QString(hex);
}

// To: Sour_xuanzi
Account::Account(const QString& name, const QString& passwd,
                 const QString& location, const QString& id)
    : m_name(name), m_location(location), m_id(id) {
    // TODO: 生成随机 16 位卡号
    m_cardNumber = generateCardNumber();
    // TODO: 将计算密码哈希值
    m_passwd = hashSHA256(passwd);
}

QString Account::generateCardNumber() {
    QString cardNumber;
    const int length = 16;
    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    // 卡号字符范围
    std::uniform_int_distribution<> dis(0, 9);

    for (int i = 0; i < length; i++) {
        QString tmp(std::to_string(dis(gen)).c_str());
        cardNumber += tmp;
    }
    return cardNumber;
}

void Account::display() const {
    U8ENCODING
    qDebug() << m_name << ' ' << m_id << ' ' << m_passwd << ' ' << m_cardNumber
             << ' ' << m_location;
}

void Account::deposit(mpf_class amount) {
    m_balance += amount;
    QDateTime currentTime = QDateTime::currentDateTime();
    m_time = currentTime.toString("yyyy-MM-dd hh:mm:ss");
}