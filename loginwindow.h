#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>
#include "Account/account.h"
#include "forgotpwd.h"
using bms::Account;


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    /// @brief 点击注册按钮
    /// @details 如果输入框隐藏，则显示输入框；否则进行注册操作
    void signup_click();

    /// @brief 点击登录按钮
    /// @details 进行登录操作
    void login_click();
    
    /// @brief 点击清空按钮
    /// @details 清空所有输入框
    void on_clear_button_clicked();

    /// @brief 点击忘记密码
    /// @details 重置密码
    void on_fogotpw_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
