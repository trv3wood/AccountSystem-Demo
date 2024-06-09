#ifndef SOURCHANGE_H
#define SOURCHANGE_H

#include <QObject>

class Sourchange : public QObject
{
    Q_OBJECT

public:
    Sourchange(QObject *parent = nullptr);

    Q_INVOKABLE void cppSlot();
};

#endif // SOURCHANGE_H
