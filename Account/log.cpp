#include "log.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <fstream>
#include <iostream>
#include <string>


Log::Log(LogType type, const std::string &id, const std::string &amount,
         const std::string &balance)
    : m_type(type), m_id(id), m_amount(amount), m_balance(balance) {}

Log::Log(LogType type, const std::string &id, const std::string &amount,
         const std::string &balance, const std::string &other)
    : m_type(type),
      m_id(id),
      m_amount(amount),
      m_balance(balance),
      m_other(other) {}

void Log::write_with(const BasicAccount &user) const {
    // qDebug() << "write_with" << QString::fromStdString(user.datafile());
    std::string filename = user.logfile();
    // qDebug() << QString::fromStdString(filename);
    // 去掉.dat后缀
    std::string log = generate_log();
    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        throw std::runtime_error("无法打开日志文件");
    }
    file.write(log.c_str());
    file.close();
}

std::string Log::generate_log() const {
    QDateTime time = QDateTime::currentDateTime();
    std::string log =
        (time.toString("yyyy-MM-dd hh:mm:ss") + " ").toStdString();
    switch (m_type) {
        case DEPOSIT:
            log += "存款";
            break;
        case WITHDRAW:
            log += "取款";
            break;
        case TRANSFEROUT:
            log += "转账";
            break;
        case TRANSFERIN:
            log += "收款";
            break;
        default:
            break;
    }
    log += " 操作人: " + m_id + " 金额: " + m_amount + " 余额: " + m_balance;
    if (m_other != "") {
        log += " 对方: " + m_other;
    }
    log += '\n';
    return log;
}

std::string Log::read_with(const BasicAccount &user) {
    std::string filename = user.logfile();
    std::fstream file(filename, std::ios::in);
    if (!file) {
        throw std::runtime_error("无法打开日志文件");
    }
    std::string log;
    std::string result;
    while (std::getline(file, log)) {
        result += log + '\n';
        // U8ENCODING
        // qDebug() << QString::fromStdString(log);
    }
    file.close();
    return result;
}

void Log::write_with(const Account &user) const {
    Log::write_with(*static_cast<const BasicAccount *>(&user));
}

std::string Log::read_with(const Account &user) {
    return Log::read_with(*static_cast<const BasicAccount *>(&user));
}
