// 记录交易信息的类
#ifndef LOG_H
#define LOG_H
#include <QtCore/QObject>
#include <string>

#include "account.h"
#include "basicAccount.h"

using bms::Encryptable, bms::BasicAccount, bms::Account;
enum LogType {
    DEPOSIT = 0,      // 存款
    WITHDRAW = 1,     // 取款
    TRANSFEROUT = 2,  // 转出
    TRANSFERIN = 3    // 转入
};
class Log {
public:
    Log() = default;
    Log(LogType type, const std::string& id, const std::string& amount,
        const std::string& balance);
    Log(LogType type, const std::string& id, const std::string& amount,
        const std::string& balance, const std::string& other);

    /// @brief 写入交易记录
    /// @param user 交易用户
    void write_with(const BasicAccount& user) const;
    void write_with(const Account& user) const;

    /// @brief 读取交易记录
    /// @param user 交易用户
    static std::string read_with(const BasicAccount& user);
    static std::string read_with(const Account& user);

    /// @brief 生成交易记录
    /// @return 交易记录
    std::string generate_log() const;

private:
    LogType m_type;            // 交易类型
    std::string m_id;          // 交易账户
    std::string m_amount;      // 交易金额
    std::string m_balance;     // 交易后余额
    std::string m_other = "";  // 交易对象
};
#endif  // LOG_H
