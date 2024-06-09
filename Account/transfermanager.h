#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include <QObject>
#include <QString>
#include <QtQuick/QQuickItem>

#include "basicAccount.h"

using bms::BasicAccount;

class TransferManager : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    TransferManager(QObject* parent = nullptr);
    TransferManager(BasicAccount& sender, const QString& receiverId, QObject* parent = nullptr);
    TransferManager(const TransferManager& other): QObject(nullptr) {
        m_sender = other.m_sender;
        m_receiver = other.m_receiver;
    }
    TransferManager operator=(const TransferManager& other) {
        m_sender = other.m_sender;
        m_receiver = other.m_receiver;
        return *this;
    }

    Q_INVOKABLE void transfer(const QString& amount);
    Q_INVOKABLE TransferManager getInstance(BasicAccount& sender,
                                        const QString& receiverId) {
        return TransferManager(sender, receiverId);
    }

private:
    BasicAccount* m_sender;
    BasicAccount* m_receiver;
};

#endif  // TRANSFERMANAGER_H
