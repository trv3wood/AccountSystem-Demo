#include "basicAccount.h"

#include <gmpxx.h>

#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "account.h"
#include "basicaccount.h"


namespace bms {
const unsigned BasicAccount::transferRestriction = 5000;

PremiumAccount:: PremiumAccount(const std::string& name, const std::string& passwd,
                 const std::string& phoneNum, const std::string& id):
                 basicAccount(name, passwd, phoneNum, id);

PremiumAccount:: PremiumAccount(const std::string& phoneNum,
                           const std::string& passwd):
                 basicAccount(phoneNum, passwdphoneNum);

void PremiumAccount::transfer(Account* to, const mpf_class& amount) {
    // Modified code without transfer limit:
m_balance -= amount;
to->m_balance += amount;
// emit balanceChanged();

#if ACCOUNT_DEBUG == 1
qDebug() << "Transfer successful!";
#endif

Log logSelf(LogType::TRANSFEROUT, static_cast<BasicAccount*>(this)->datafile(), Serializable::mpf_class2str(amount), balance());
logSelf.write_with(*this);
Log logTo(LogType::TRANSFERIN, static_cast<BasicAccount*>(to)->datafile(), Serializable::mpf_class2str(amount), to->balance());
logTo.write_with(*to);
}
                 
}
