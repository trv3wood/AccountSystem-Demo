#ifndef BASICACCOUNT_H
#define BASICACCOUNT_H
#include <QtCore/QStringList>
#include <QtCore/QObject>
#include <string>

#include "Encryptable/Encryptable.h"
#include "Serializable.h"
#include "account.h"

namespace bms {
class BasicAccount : public Account, public Serializable, public Encryptable {
    Q_OBJECT
public:
    BasicAccount() = default;
    /// @brief 构造函数
    /// @param name 用户名
    /// @param passwd 密码
    /// @param phoneNum 手机号
    /// @param id 身份证号
    /// @note 应当用于注册新账户
    BasicAccount(const std::string& name, const std::string& passwd,
                 const std::string& phoneNum, const std::string& id);

    /// @brief 构造函数
    /// @param phoneNum 手机号
    /// @param passwd 密码
    /// @note 应当用于登录已有账户
    BasicAccount(const std::string& phoneNum, const std::string& passwd);

private:
    static const unsigned transferRestriction;
    /// @brief 数据文件名
    /// @note 用于存储加密后的账户信息
    /// @note 命名格式为：手机号的hash值取前8位+后缀".dat"
    std::string m_datafile;

    /// @brief 日志文件名
    /// @note 用于存储加密后的日志信息
    /// @note 命名格式为：手机号的hash值取前8位+后缀".log"
    std::string m_logfile;

    /// @brief 将账户信息序列化为字符串
    /// @param data 序列化后的字符串
    void serialize(std::string& data) const override;
    /// @brief 从字符串中解析出账户信息
    /// @param data 序列化后的字符串
    void deserialize(const std::string& data) override;

public:
    /// @brief 获取数据文件名
    /// @note 命名格式为：手机号的hash值取前8位+后缀".dat"
    std::string datafile() const { return m_datafile; }

    /// @brief 获取日志文件名
    /// @note 命名格式为：手机号的hash值取前8位+后缀".log"
    std::string logfile() const { return m_logfile; }

    /// @brief 存款
    /// @param amount 存款金额
    /// @param to 转入账户
    /// @return 存款后的余额
    void transfer(Account* to, const mpf_class& amount) override;
    /// @brief 暴露给QML的转账接口
    Q_INVOKABLE virtual void transfer(const QString& phone, const QString& amount);

    /// @brief 将类的信息存储到文件
    /// @param filename 文件名
    /// @note 文件名搭配datafile()使用
    void store(const std::string& filename);
    Q_INVOKABLE void store();

    /// @brief 从文件中加载类的信息
    /// @param filename 文件名
    /// @note 文件名搭配datafile()使用
    void load(const std::string& filename);
    Q_INVOKABLE void load();

    Q_INVOKABLE void setPasswd(const std::string& passwd) override;

    Q_INVOKABLE void deposit(const QString& amount) override;
    Q_INVOKABLE void withdraw(const QString& amount) override;

    /// @brief 获取最近的交易记录
    Q_INVOKABLE QStringList recentRecords() const;
    /// @brief 获取最近的转账对象
    Q_INVOKABLE QStringList recentTransfers() const;
};
}  // namespace bms
#endif  // BASICACCOUNT_H
