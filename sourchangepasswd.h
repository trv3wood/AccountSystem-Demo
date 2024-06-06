#ifndef SOURCHANGEPASSWD_H
#define SOURCHANGEPASSWD_H

#include <QObject>
#include"forgotpwd.h"

class Sourchangepasswd : public QObject
{
    Q_OBJECT
public:
    explicit Sourchangepasswd(forgotpwd *widget, QObject *parent = nullptr);

public slots:
    void callForgotPwdClicked();

private:
    forgotpwd *m_forgotPwdWidget;
};


#endif // SOURCHANGEPASSWD_H
