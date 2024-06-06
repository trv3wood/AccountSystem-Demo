#include "sourchangepasswd.h"

Sourchangepasswd::Sourchangepasswd(forgotpwd *widget, QObject *parent) : QObject(parent), m_forgotPwdWidget(widget)
{

}

void Sourchangepasswd::callForgotPwdClicked()
{
    m_forgotPwdWidget->on_fogotpw_clicked();
}
