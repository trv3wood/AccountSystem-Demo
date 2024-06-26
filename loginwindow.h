#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cppConnection();
private slots:
    /// @brief 点击注册按钮
    /// @details 如果输入框隐藏，则显示输入框；否则进行注册操作
    void signup_click();

    /// @brief 点击登录按钮
    /// @details 进行登录操作
    void login_click();
    
    /// @brief 点击清空按钮
    /// @details 清空所有输入框
    void clear_button_click();

    void fogotpw_click();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
