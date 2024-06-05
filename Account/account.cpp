#include "account.h"

#include <gmpxx.h>

#include <QString>
#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include <QtWidgets/QMessageBox>

#if ACCOUNT_DEBUG == 1
#include <cassert>
#endif

using bms::Account;

QString Account::name() const { return QString::fromStdString(m_name); }

QString Account::passwd() const { return QString::fromStdString(m_passwd); }

QString Account::phoneNum() const { return QString::fromStdString(m_phonenumber); }

QString Account::id() const { return QString::fromStdString(m_id); }

mpf_class Account::balance() const { return m_balance; }

mpf_class Account::interestRate() const { return m_interestRate; }

QString Account::cardNumber() const {
    return QString::fromStdString(m_cardNumber);
}

void Account::setName(const std::string& name) { m_name = name; }

void Account::setPasswd(const std::string& passwd) {
    m_passwd = passwd;
    // emit passwdChanged();
}

void Account::setLocation(const std::string& location) {
    m_phonenumber = location;
}

void Account::setId(const std::string& id) { m_id = id; }

void Account::setInterestRate(double rate) { m_interestRate = rate; }

void Account::transfer(Account* to, const mpf_class& amount) {
    if (m_balance >= amount) {
        m_balance -= amount;
        to->m_balance += amount;
        // emit balanceChanged();
#if ACCOUNT_DEBUG == 1
        qDebug() << "Transfer successful!";
#endif
    } else {
        QMessageBox::information(nullptr, "Title", "余额不足");
    }
}

// To: Sour_xuanzi
Account::Account(const std::string& name, const std::string& passwd,
                 const std::string& phoneNum, const std::string& id, QObject *parent)
    : QObject(parent),
      m_name(name),
      m_passwd(passwd),
      m_phonenumber(phoneNum),
      m_id(id),
      m_cardNumber(generateCardNumber()),
      m_balance("0.0"),
      m_interestRate("0.01") {}

Account::Account(const std::string& phoneNum, const std::string& passwd, QObject *parent)
    : QObject(parent),
      m_name("user"),
      m_passwd(passwd),
      m_phonenumber(phoneNum),
      m_id("0"),
      m_cardNumber("00000000"),
      m_balance("0.0"),
      m_interestRate("0.01") {}

std::string Account::generateCardNumber() {
    std::string cardNumber;
    const int len = 16;

    // 检查处理器是否支持 rdrand 指令
    bool rdrandSupported = false;
    unsigned int eax, ebx, ecx, edx;
    __asm__ volatile("cpuid"
                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                     : "a"(1));
    if (ecx & 0x40000000) {
        rdrandSupported = true;
    }

    if (rdrandSupported) {
        // 使用 rdrand 生成随机数
        while (cardNumber.length() < len) {
            unsigned int cardNumberInt;
            unsigned char success;
            __asm__ volatile("rdrand %0; setc %1"
                             : "=r"(cardNumberInt), "=qm"(success));
            if (success) {
                cardNumber += std::to_string(cardNumberInt % 10);
            }
        }
    } else {
        // 使用标准库生成随机数
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 9);
        for (int i = 0; i < len; ++i) {
            cardNumber += std::to_string(dis(gen));
        }
    }

    return cardNumber;
}

void Account::display() const {
    U8ENCODING
    std::cout << "Name: " << m_name << '\n'
              << "ID: " << m_id << '\n'
              << "Password: " << m_passwd << '\n'
              << "Card Number: " << m_cardNumber << '\n'
              << "Location: " << m_phonenumber << '\n'
              << "Balance: " << m_balance << '\n'
              << "Interest Rate: " << m_interestRate << "\n\n";
}

void Account::deposit(const mpf_class& amount) { m_balance += amount; }
