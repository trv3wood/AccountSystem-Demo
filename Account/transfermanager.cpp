#include "transfermanager.h"

#include <gmpxx.h>
#include <qobject.h>

#include <QMessageBox>

TransferManager::TransferManager(QObject *parent) : QObject(parent) {}

TransferManager::TransferManager(BasicAccount &sender,
                                 const QString &receiverId, QObject *parent)
    : QObject(parent),
      m_sender(&sender),
      m_receiver(new BasicAccount(receiverId.toStdString(), ".")) {
    // 检查账户是否存在
    if (!QFile::exists(QString::fromStdString(m_receiver->datafile()))) {
#if ACCOUNT_DEBUG == 1
        qDebug() << __FUNCTION__ << "Account not found!";
#endif
        QMessageBox::warning(nullptr, "账户", "账户不存在！");
        return;
    }
    m_receiver->load();
}

void TransferManager::transfer(const QString &amount) {
    if (m_sender == nullptr || m_receiver == nullptr) {
#if ACCOUNT_DEBUG == 1
        qDebug() << __FUNCTION__ << "Account not found!";
#endif
        QMessageBox::warning(nullptr, "账户", "账户不存在！");
        return;
    }
    m_sender->transfer(m_receiver, mpf_class(amount.toStdString()));
}
