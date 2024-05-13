#include "account.h"
#include <openssl/sha.h>
#if ACCOUNT_DEBUG == 1
#include <cassert>
#include <stdexcept>
#endif
using bms::Account;

QString Account::name() const { return m_name; }

QString Account::passwd() const { return m_passwd; }

QString Account::location() const { return m_location; }

unsigned Account::id() const { return m_id; }

void Account::setName(const QString &name) { m_name = name; }

void Account::setPasswd(const QString &passwd) { m_passwd = hashSHA256(passwd); }

void Account::setLocation(const QString &location) { m_location = location; }

void Account::setId(unsigned id) { m_id = id; }

void Account::setInterestRate(double rate) { m_interestRate = rate; }

QString Account::hashSHA256(const QString& passwd) {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // 32 字节的哈希值
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwd.toStdString().c_str(), passwd.length());
    SHA256_Final(hash, &sha256);
    char hex[2 * SHA256_DIGEST_LENGTH + 1]; // 64 字节的十六进制字符串
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex + 2 * i, "%02x", hash[i]); // 两个字符表示一个字节
    }
    hex[2 * SHA256_DIGEST_LENGTH] = 0; // 字符串结尾
    return QString(hex);
}

// To: Sour_xuanzi
Account::Account(const QString& name, const QString& passwd, const QString& location, unsigned id): m_name(name), m_location(location), m_id(id) {
    // TODO: 生成随机 16 位卡号

    #if ACCOUNT_DEBUG == 1
    int origin = m_cardNumber;
    #endif
    // TODO: 将计算密码哈希值
    m_passwd = hashSHA256(passwd);
    // 测试代码
    #if ACCOUNT_DEBUG == 1
    U8ENCODING
    qDebug() << "Account::Account()" << m_name << m_passwd << m_location;
    if (passwd == m_passwd) {
        throw std::invalid_argument("can not store password in plain text!");
    } 
    assert(m_cardNumber != origin);
    #endif
}

#if ACCOUNT_DEBUG == 1
void Account::display() const {
    U8ENCODING
    qDebug() << m_name << ' ' << m_id << ' ' << m_passwd << ' ' << m_cardNumber << ' ' << m_location;
}
#endif
/// @brief 存款
   /// @param amount 存款金额
   /// @note 未完成，分配给 Maco
void Account::deposit(unsigned amount)
{
    m_balance += amount;
}