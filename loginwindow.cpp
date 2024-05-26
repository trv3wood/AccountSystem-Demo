#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QWidget>
// #include"sign_up.h"
#include "Account/basicAccount.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->idEdit->hide();
    ui->nameEdit->hide();
    ui->passwdConfirm->hide();
    QObject::connect(ui->sign_up_btn, SIGNAL(clicked()), this, SLOT(signup_click()));
    QObject::connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(login_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

static bool checkPasswdStrength(const QString &passwd) {
    if (passwd.length() < 8) {
        return false;
    }
    if (passwd.contains(QRegExp("[0-9]"))) {
        if (passwd.contains(QRegExp("[a-z]"))) {
            if (passwd.contains(QRegExp("[A-Z]"))) {
                return true;
            }
        }
    }
    return false;
}

static void showErrWindow(const QString& errMsg) {
    QMessageBox* err = new QMessageBox;
    err->setText(errMsg);
    err->resize(400, 300);
    err->show();
}
void MainWindow::signup_click() {
    if (ui->idEdit->isHidden()) {
        ui->idEdit->show();
        ui->nameEdit->show();
        ui->passwdConfirm->show();
        return;
    }
    QString phone = ui->phoneEdit->text();
    QString passwd = ui->passwdEdit->text();
    QString id = ui->idEdit->text();
    QString name = ui->nameEdit->text();
    if (phone.isEmpty()) {
        showErrWindow("手机号不能为空");
        return;
    }
    if (id.isEmpty()) {
        showErrWindow("身份证号不能为空");
        return;
    }
    if (name.isEmpty()) {
        showErrWindow("姓名不能为空");
        return;
    }
    if (passwd != ui->passwdConfirm->text()) {
        showErrWindow("两次输入密码不一致");
        return;
    }
    // 检查密码强度
    if (!checkPasswdStrength(passwd)) {
        showErrWindow("密码强度不足");
        return;
    }
    bms::BasicAccount account("name", passwd.toStdString(), "nowhere", phone .toStdString());
    account.store(account.datafile());
}

void MainWindow::login_click() {
    if (ui->idEdit->isVisible()) {
        ui->idEdit->hide();
        ui->nameEdit->hide();
        ui->passwdConfirm->hide();
        return;
    }
    // TODO 完成登录逻辑
}

// void MainWindow::sign_up_clicked()
// {
//     this->hide();
//     Sign_up*x=new Sign_up;//打开注册的窗口
//     x->show();
// }

