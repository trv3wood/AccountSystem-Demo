#include "account.h"
#include <openssl/sha.h>
#include <QString>
#include <string>

#if ACCOUNT_DEBUG == 1
#include <cassert>
#endif

using bms::Account;

QString Account::name() const { return m_name; }

QString Account::passwd() const { return m_passwd; }

QString Account::location() const { return m_location; }

unsigned Account::id() const { return m_id; }

void Account::setName(const QString& name) { m_name = name; }

void Account::setPasswd(const QString& passwd) {
    m_passwd = hashSHA256(passwd);
}

void Account::setLocation(const QString& location) { m_location = location; }

void Account::setId(unsigned id) { m_id = id; }

void Account::setInterestRate(double rate) { m_interestRate = rate; }

void Account::transfer(Account& to, unsigned amount) {
    if (m_balance >= amount) {
        m_balance -= amount;
        to.m_balance += amount;
        QDateTime currentTime = QDateTime::currentDateTime();
        m_time = currentTime.toString("yyyy-MM-dd hh:mm:ss");
#if ACCOUNT_DEBUG == 1
        qDebug() << "Transfer successful!";
#endif
    } else {
        std::string msg = "Insufficient balance!";
        msg += " Current balance: " + std::to_string(m_balance);
        msg += " Transfer amount: " + std::to_string(amount);
        throw std::invalid_argument(msg.c_str());
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
                 const QString& location, unsigned id)
    : m_name(name),
      m_location(location),
      m_id(id)
{
#if ACCOUNT_DEBUG == 1
    QString origin = m_cardNumber;
#endif
    // TODO: 生成随机 16 位卡号
    m_cardNumber = generateCardNumber();
    // TODO: 将计算密码哈希值
    m_passwd = hashSHA256(passwd);
// 测试代码
#if ACCOUNT_DEBUG == 1
    display();
    if (passwd == m_passwd) {
        throw std::invalid_argument("can not store password in plain text!");
    }
    assert(m_cardNumber != origin);
#endif
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
/// @brief 存款
   /// @param amount 存款金额
   /// @note 未完成，分配给 Maco
void Account::deposit(unsigned amount)
{
    m_balance += amount;
}