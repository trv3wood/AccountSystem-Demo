#include "account.h"

#include <gmp.h>
#include <gmpxx.h>

#include <QString>
#include <QtWidgets/QMessageBox>
#include <iostream>
#include <random>
#include <string>

#include "Serializable.h"
#include "basicAccount.h"
#include "log.h"

using bms::Account;

QString Account::name() const { return QString::fromStdString(m_name); }

QString Account::passwd() const { return QString::fromStdString(m_passwd); }

QString Account::phoneNum() const {
    return QString::fromStdString(m_phonenumber);
}

QString Account::id() const { return QString::fromStdString(m_id); }

QString Account::balance_f() const {
    return QString::fromStdString(Serializable::mpf_class2str(m_balance));
}

QString Account::interestRate_f() const {
    return QString::fromStdString(Serializable::mpf_class2str(m_interestRate));
}

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
        m_balance.set_prec(3);
        if (roundBalance()) {
            m_balance = 0.01;
        }
        static_cast<BasicAccount*>(this)->store();
        emit balanceChanged();
        to->m_balance += amount;
        BasicAccount* castTo = static_cast<BasicAccount*>(to);
        castTo->store();
        emit to->balanceChanged();

#if ACCOUNT_DEBUG == 1
        qDebug() << "Transfer successful!" << "self balance: " << Balance() << " to balance: " << to->Balance();
#endif
        QMessageBox::information(nullptr, "转账", "转账成功！");
        Log logSelf(LogType::TRANSFEROUT,
                    static_cast<BasicAccount*>(this)->datafile(),
                    Serializable::mpf_class2str(amount),
                    Balance().toStdString(), to->id().toStdString());
        logSelf.write_with(*this);
        Log logTo(LogType::TRANSFERIN,
                  m_phonenumber,
                  Serializable::mpf_class2str(amount),
                  to->Balance().toStdString(), id().toStdString());
        logTo.write_with(*to);
    } else {
#if ACCOUNT_DEBUG == 1
        qDebug() << "Insufficient balance!";
#endif
        QMessageBox::warning(nullptr, "转账", "余额不足！");
    }
}

// To: Sour_xuanzi
Account::Account(const std::string& name, const std::string& passwd,
                 const std::string& phoneNum, const std::string& id,
                 QObject* parent)
    : QObject(parent),
      m_name(name),
      m_passwd(passwd),
      m_phonenumber(phoneNum),
      m_id(id),
      m_cardNumber(generateCardNumber()),
      m_balance("0.0"),
      m_interestRate("0.01") {}

Account::Account(const std::string& phoneNum, const std::string& passwd,
                 QObject* parent)
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

void Account::deposit(const mpf_class& amount) {
#if ACCOUNT_DEBUG == 1
    std::cout << "Deposit amount: " << amount << std::endl;
    std::cout << "write_with" << Serializable::mpf_class2str(amount)
              << std::endl;
#endif
    m_balance += amount;
    static_cast<BasicAccount*>(this)->store();
    emit balanceChanged();
    Log log(LogType::DEPOSIT, m_phonenumber, Serializable::mpf_class2str(amount),
            balance_f().toStdString());

    log.write_with(*this);

#if ACCOUNT_DEBUG == 1
    qDebug() << "Deposit successful!";
#endif
    QMessageBox::information(nullptr, "存款", "存款成功！");
}
void Account::deposit(const QString& amount) {
#if ACCOUNT_DEBUG == 1
    qDebug() << "Deposit amount: " << amount;
#endif
    Account::deposit(mpf_class(amount.toStdString()));
}

bool Account::roundBalance() const {
    QString balance = Balance();
    if (balance.endsWith("e-2") && balance.startsWith("9")) {
        return true;
    }
    return false;
}
void Account::withdraw(const mpf_class& amount) {
    if (m_balance >= amount) {
        m_balance -= amount;
        m_balance.set_prec(3);
        if (roundBalance()) {
            m_balance = 0.01;
        }
        static_cast<BasicAccount*>(this)->store();
        emit balanceChanged();
#if ACCOUNT_DEBUG == 1
        qDebug() << "Withdraw successful!";
#endif
        QMessageBox::information(nullptr, "Withdraw", "Withdraw successful!");
        Log log(LogType::WITHDRAW, m_phonenumber, Serializable::mpf_class2str(amount),
                balance_f().toStdString());
        log.write_with(*this);
    } else {
        qDebug() << "Insufficient balance!";
        QMessageBox::warning(nullptr, "取款", "余额不足！");
    }
}

void Account::withdraw(const QString& amount) {
#if ACCOUNT_DEBUG == 1
    qDebug() << "Withdraw amount: " << amount;
#endif
    Account::withdraw(mpf_class(amount.toStdString()));
}
