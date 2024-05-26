#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>
#include"forgotpwd.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    forgotpwd*next=NULL;
private slots:
    void signup_click();
    void login_click();

// private slots:
//     void on_sign_up_clicked();

    void on_fogotpw_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
