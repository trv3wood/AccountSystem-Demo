#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <gmpxx.h>

#include <QtCore/QDateTime>
#include <QtCore/QString>
#include <random>
#include <stdexcept>
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
}
class bms::Account {
private:
    QString m_name;      // 用户姓名
    QString m_passwd;    // 密码
    QString m_location;  // 常住地址
    QString m_id;        // 身份证号码，用户的唯一标识
    QString m_time;      // 记录操作时间

    mpf_class m_balance;  // 余额
    mpf_class m_interestRate;  // 利率

    QString m_cardNumber;  // 卡号，由系统生成，用于交易和识别

public:
    Account() {}

    /// @brief 构造函数
    /// @param name 用户姓名
    /// @param passwd 用户密码
    /// @param location 用户常住地址
    /// @note 生成卡号和密码哈希值，完成，分配给 Sour_xuanzi
    /// @note 考虑加密用户信息
    Account(const QString& name, const QString& passwd, const QString& location,
            const QString& id);

    QString name() const;
    QString passwd() const;
    QString location() const;
    QString id() const;

    mpf_class balance() const;
    mpf_class interestRate() const;
    QString cardNumber() const;

    void setName(const QString& name);
    void setPasswd(const QString& passwd);
    void setLocation(const QString& location);

    /// @brief 设置用户的唯一标识
    /// @param id 用户的唯一标识
    /// @note 完成
    /// @note 考虑加密，毕竟是身份证号码
    void setId(const QString& id);

    void setInterestRate(double rate);

    /// @brief 转账
    /// @param to 转账目标
    /// @param amount 转账金额
    /// @note 完成，分配给 Muscle
    /// @note 派生类的转账限额不同，需要重写
    virtual void transfer(Account& to, mpf_class amount);

    /// @brief 存款
    /// @param amount 存款金额
    /// @note 完成，分配给 Maco
    void deposit(mpf_class amount);

    void display() const;

private:
    /// @brief 生成随机卡号
    /// @return 卡号 16 位
    /// @note 完成，分配给 Sour_xuanzi
    QString generateCardNumber();

    /// @brief 计算密码哈希值
    /// @param str 用户密码
    /// @return 哈希值
    /// @note 使用了SHA256 算法 completed by Z_MAHO
    static QString hashSHA256(const QString& str);
};
#endif
