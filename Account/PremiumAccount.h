#ifndef PREMIUMACCOUNT_H
#define PREMIUMACCOUNT_H
#include <string>
#include <QtCore/QObject>

#include "Encryptable/Encryptable.h"
#include "Serializable.h"
#include "account.h"
#include "basicaccount.h"

namespace bms {
class PremiumAccount : public BasicAccount, public Serializable, public Encryptable {
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

private:
    

public:
/// @brief 存款
    /// @param amount 存款金额
    /// @param to 转入账户
    /// @return 存款后的余额
    Q_INVOKABLE void transfer(Account* to, const mpf_class& amount) override;
    
};
}  // namespace bms
#endif  // PREMIUMACCOUNT_H 