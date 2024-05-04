#ifndef ACCOUNT_H
#define ACCOUNT_H

#define ACCOUNT_DEBUG 1
#if ACCOUNT_DEBUG == 1
#include <QtCore/QDebug>
#include <QtCore/QTextCodec>
#define U8ENCODING QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

#include <QtCore/QString>
namespace bms { class Account; }
class bms::Account {
private:
    QString m_name; // 用户姓名
    QString m_passwd; // 密码
    QString m_location; // 常住地址
    unsigned m_id; // 身份证号码，用户的唯一标识

    unsigned m_balance; // 余额，有溢出风险，后期用gmplib或自己实现
    double m_interestRate; // 利率，精度问题，后期用gmplib或自己实现

    int m_cardNumber; // 卡号，由系统生成，用于交易和识别

public:
    Account() {}

    /// @brief 构造函数
    /// @param name 用户姓名
    /// @param passwd 用户密码
    /// @param location 用户常住地址
    /// @note 生成卡号和密码哈希值，未完成，分配给 Sour_xuanzi
    /// @note 考虑加密用户信息
    Account(const QString& name, const QString& passwd, const QString& location, unsigned id);

    QString name() const;
    QString passwd() const;
    QString location() const;
    unsigned id() const;

    // 未完成
    unsigned balance() const;
    double interestRate() const;
    unsigned cardNumber() const;
    // 未完成

    void setName(const QString& name);
    void setPasswd(const QString& passwd);
    void setLocation(const QString& location);

    /// @brief 设置用户的唯一标识
    /// @param id 用户的唯一标识
    /// @note 未完成 考虑加密，毕竟是身份证号码
    void setId(unsigned id);

    void setInterestRate(double rate);

    /// @brief 转账
    /// @param to 转账目标
    /// @param amount 转账金额
    /// @note 未完成，分配给 Muscle
    /// @note 派生类的转账限额不同，需要重写
    virtual void transfer(Account& to, unsigned amount);

    /// @brief 存款
    /// @param amount 存款金额
    /// @note 未完成，分配给 Maco
    void deposit(unsigned amount);

    #if ACCOUNT_DEBUG == 1
    void display() const;
    #endif
private:
    /// @brief 生成随机卡号
    /// @return 卡号 16 位
    /// @note 未完成，分配给 Sour_xuanzi
    unsigned generateCardNumber();

    /// @brief 计算密码哈希值
    /// @param passwd 用户密码
    /// @return 哈希值
    /// @note 使用了SHA256 算法 completed by Z_MAHO
    QString hashSHA256(const QString& passwd);
};
#endif