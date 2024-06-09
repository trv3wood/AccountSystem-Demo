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
    // 日志文件名
    std::string filename = user.logfile();
    // 超过一定大小则清空
    QFile file(QString::fromStdString(filename));
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly)) {
            throw std::runtime_error("无法打开日志文件");
        }
        file.close();
    } else {
        if (file.size() > 1024 * 1024 * 10) {
            if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                throw std::runtime_error("无法打开日志文件");
            }
            file.close();
        }
    }

    // 生成日志
    std::string log = generate_log();
    // 写入日志
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        throw std::runtime_error("无法打开日志文件");
    }
    file.write(log.c_str());
    file.close();
}

std::string Log::generate_log() const {
    // 交易时间
    QDateTime time = QDateTime::currentDateTime();
    std::string log =
        (time.toString("yyyy-MM-dd hh:mm:ss") + " ").toStdString();
    // 交易类型
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
    // 交易信息
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
