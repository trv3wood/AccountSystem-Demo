#include "account.h"
#include <openssl/sha.h>
#if ACCOUNT_DEBUG == 1
#include <cassert>
#endif
#include<QString>
#include<string>
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
Account::Account(const QString& name, const QString& passwd, const QString& location, unsigned id): m_name(name), m_location(location), m_id(id) 
    // TODO: 生成随机 16 位卡号
    {
        m_cardNumber = QString generateCardNumber();
        hashSHA256(QString& m_passwd);
            #if ACCOUNT_DEBUG == 1
        QString origin = m_cardNumber;
        #endif
        // TODO: 将计算密码哈希值
        hashSHA256(passwd);
        // 测试代码
        #if ACCOUNT_DEBUG == 1
        U8ENCODING
        qDebug() << "Account::Account()" << m_name << m_passwd << m_location;
        if (passwd == m_passwd) {
            throw std::invalid_argument("can not store password in plain text!");
        } 
        assert(m_cardNumber != origin);
        #endif
    };
QString Account:: generateCardNumber() {
    QString m_cardNumber;
    const int length = 16;
    //随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    //卡号字符范围
    std::uniform_int_distribution<> dis(0, 9);

    for (int i = 0; i < length; i++) {
        QString tmp = std::to_string(dis(gen));
        m_cardNumber += tmp;
    }
    };

}

#if ACCOUNT_DEBUG == 1
void Account::display() const {
    U8ENCODING
    qDebug() << m_name << ' ' << m_id << ' ' << m_passwd << ' ' << m_cardNumber << ' ' << m_location;
}
#endif