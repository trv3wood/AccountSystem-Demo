#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <gmpxx.h>

#include <QtCore/QString>
#include <string>

#define ACCOUNT_DEBUG 1
#if ACCOUNT_DEBUG == 1
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#define U8ENCODING \
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

namespace bms {
class Account;
const double defualtInterestRate = 0.01;
}
class bms::Account {
protected:
    std::string m_name;        // 用户姓名
    std::string m_passwd;      // 密码
    std::string m_location;    // 常住地址
    std::string m_id;          // 身份证号码，用户的唯一标识
    std::string m_cardNumber;  // 卡号，由系统生成，用于交易和识别

    mpf_class m_balance;   // 余额
    mpf_class m_interestRate;  // 利率

public:
    Account(): m_balance(0), m_interestRate(defualtInterestRate) {}
    virtual ~Account() {}

    /// @brief 构造函数
    /// @param name 用户姓名
    /// @param passwd 用户密码
    /// @param location 用户常住地址
    /// @note 生成卡号和密码哈希值，完成，分配给 Sour_xuanzi
    /// @note 考虑加密用户信息
    Account(const std::string& name, const std::string& passwd,
            const std::string& location, const std::string& id);

    QString name() const;
    QString passwd() const;
    QString location() const;
    QString id() const;

    mpf_class balance() const;
    mpf_class interestRate() const;
    QString cardNumber() const;

    void setName(const std::string& name);
    virtual void setPasswd(const std::string& passwd);
    void setLocation(const std::string& location);

    /// @brief 设置用户的唯一标识
    /// @param id 用户的唯一标识
    /// @note 完成
    /// @note 考虑加密，毕竟是身份证号码
    void setId(const std::string& id);

    void setInterestRate(double rate);

    /// @brief 转账
    /// @param to 转账目标
    /// @param amount 转账金额
    /// @note 完成，分配给 Muscle
    /// @note 派生类的转账限额不同，需要重写
    virtual void transfer(Account* to, const mpf_class& amount);

    /// @brief 存款
    /// @param amount 存款金额
    /// @note 完成，分配给 Maco
    virtual void deposit(const mpf_class& amount);

    void display() const;

private:
    /// @brief 生成随机卡号
    /// @return 卡号 16 位
    /// @note 完成，分配给 Sour_xuanzi
    static std::string generateCardNumber();
protected:

    static std::string mpf_class2str(const mpf_class& number);
};
#endif
