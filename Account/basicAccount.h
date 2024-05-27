#include <string>

#include "Encryptable/Encryptable.h"
#include "Serializable/Serializable.h"
#include "account.h"

namespace bms {
class BasicAccount : public Account, public Serializable, public Encryptable {
public:
    BasicAccount() = default;
    BasicAccount(const std::string& name, const std::string& passwd,
                 const std::string& location, const std::string& id);

private:
    static const unsigned transferRestriction;
    /// @brief 数据文件名
    /// @note 用于存储加密后的账户信息
    /// @note 命名格式为：手机号的hash值取前8位+后缀".dat"
    std::string m_datafile;

    /// @brief 将账户信息序列化为字符串
    /// @param data 序列化后的字符串
    void serialize(std::string& data) const override;
    /// @brief 从字符串中解析出账户信息
    /// @param data 序列化后的字符串
    void deserialize(const std::string& data) override;

public:
    /// @brief 获取数据文件名
    std::string datafile() const { return m_datafile; }
    /// @brief 存款
    /// @param amount 存款金额
    /// @param to 转入账户
    /// @return 存款后的余额
    void transfer(Account* to, const mpf_class& amount) override;

    /// @brief 将类的信息存储到文件
    /// @param filename 文件名
    /// @note 文件名搭配datafile()使用
    void store(const std::string& filename);

    /// @brief 从文件中加载类的信息
    /// @param filename 文件名
    /// @note 文件名搭配datafile()使用
    void load(const std::string& filename);
};
}  // namespace bms