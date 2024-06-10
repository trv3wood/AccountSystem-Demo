#include "PremiumAccount.h"

#include <gmpxx.h>
#include <QRegExp>

#include <string>
#include <QFile>
#include <QMessageBox>
#include "account.h"
#include "basicaccount.h"

namespace bms {

PremiumAccount::PremiumAccount(const std::string& name,
                               const std::string& passwd,
                               const std::string& phoneNum,
                               const std::string& id)
    : BasicAccount(name, passwd, phoneNum, id){};

PremiumAccount::PremiumAccount(const std::string& phoneNum,
                               const std::string& passwd)
    : BasicAccount(phoneNum, passwd){}

void PremiumAccount::transfer(const QString &phone, const QString &amount) {
    // 同步转出账户信息
    load();
    BasicAccount to(phone.toStdString(), ".");
    // 检查转入账户是否存在
    if (!QFile(to.datafile().c_str()).exists()) {
        QMessageBox::warning(nullptr, "不存在", "转入账户不存在");
        return;
    }
    // 同步转入账户信息
    to.load();
    Account::transfer(&to, mpf_class(amount.toStdString()));
}

bool PremiumAccount::isPremium(const QString &phoneNum) {
    QRegExp re("\\d*[02468]$");
    return re.exactMatch(phoneNum);
};

}  // namespace bms
