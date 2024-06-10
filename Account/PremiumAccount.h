#ifndef PREMIUMACCOUNT_H
#define PREMIUMACCOUNT_H
#include <QtCore/QObject>
#include <string>

#include "basicaccount.h"

namespace bms {
class PremiumAccount : public BasicAccount {
    Q_OBJECT
public:
    PremiumAccount() = default;
    /// @brief 构造函数
    /// @param name 用户名
    /// @param passwd 密码
    /// @param phoneNum 手机号
    /// @param id 身份证号
    /// @note 应当用于注册新账户
    PremiumAccount(const std::string& name, const std::string& passwd,
                   const std::string& phoneNum, const std::string& id);

    /// @brief 构造函数
    /// @param phoneNum 手机号
    /// @param passwd 密码
    /// @note 应当用于登录已有账户
    PremiumAccount(const std::string& phoneNum, const std::string& passwd);

    /// @brief 暴露给QML的转账接口
    /// @param phone 转账目标
    /// @param amount 转账金额
    Q_INVOKABLE void transfer(const QString& phone,
                              const QString& amount) override;
    /// @brief 判断是否为高级用户
    /// @param phoneNum 手机号
    /// @return 是否为高级用户
    /// @note 高级用户的手机号为偶数结尾
    Q_INVOKABLE static bool isPremium(const QString& phoneNum);
};
}  // namespace bms
#endif  // PREMIUMACCOUNT_H
