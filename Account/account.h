#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <gmpxx.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <string>

#include "Serializable.h"

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
}  // namespace bms
class bms::Account : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString passwd READ passwd CONSTANT)
    Q_PROPERTY(QString phoneNum READ phoneNum CONSTANT)
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString balance READ Balance WRITE deposit WRITE withdraw NOTIFY
                   balanceChanged)
    Q_PROPERTY(QString balance_f READ balance_f WRITE deposit WRITE withdraw
                   NOTIFY balanceChanged)
    Q_PROPERTY(
        QString interestRate READ InterestRate READ interestRate_f CONSTANT)
    Q_PROPERTY(QString cardNumber READ cardNumber CONSTANT)
protected:
    std::string m_name;         // 用户姓名
    std::string m_passwd;       // 密码
    std::string m_phonenumber;  // 手机号
    std::string m_id;           // 身份证号码，用户的唯一标识
    std::string m_cardNumber;  // 卡号，由系统生成，用于交易和识别

    mpf_class m_balance;       // 余额
    mpf_class m_interestRate;  // 利率

signals:
    void balanceChanged();

public:
    Account()
        : QObject(nullptr), m_balance(0), m_interestRate(defualtInterestRate) {}
    virtual ~Account() {}

    /// @brief 构造函数
    /// @param name 用户姓名
    /// @param passwd 用户密码
    /// @param phoneNum 用户手机号
    /// @note 生成卡号和密码哈希值，完成，分配给 Sour_xuanzi
    /// @note 考虑加密用户信息
    Account(const std::string& name, const std::string& passwd,
            const std::string& phoneNum, const std::string& id,
            QObject* parent = nullptr);

    /// @brief 构造函数
    /// @param phoneNum 用户手机号
    /// @param passwd 用户密码
    /// @note 应当用于登录已有账户
    Account(const std::string& phoneNum, const std::string& passwd,
            QObject* parent = nullptr);

    QString name() const;
    QString passwd() const;
    QString phoneNum() const;
    QString id() const;

    /// @brief 获取余额
    /// @return 计算机科学中的字符串表示，e.g. "1.23e+4"
    QString Balance() const { return Serializable::mpf2str(m_balance); }
    QString InterestRate() const {
        return Serializable::mpf2str(m_interestRate);
    }

    /// @brief 获取余额
    /// @return 人类可读的字符串表示，e.g. "12,345.67"
    QString balance_f() const;
    QString interestRate_f() const;
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
    Q_INVOKABLE virtual void transfer(Account* to, const mpf_class& amount);

    /// @brief 存款
    /// @param amount 存款金额
    /// @note 完成，分配给 Maco
    void deposit(const mpf_class& amount);
    /// @brief 暴露给 QML 的存款接口
    Q_INVOKABLE virtual void deposit(const QString& amount);

    /// @brief 取款
    /// @param amount 取款金额
    void withdraw(const mpf_class& amount);

    /// @brief 暴露给 QML 的取款接口
    Q_INVOKABLE virtual void withdraw(const QString& amount);
    
    /// @brief 打印账户信息，用于调试
    void display() const;

private:
    /// @brief 生成随机卡号
    /// @return 卡号 16 位
    /// @note 完成，分配给 Sour_xuanzi
    static std::string generateCardNumber();

    /// @brief 检查余额舍入
    /// @return 是否舍入
    bool roundBalance() const;
};
#endif
