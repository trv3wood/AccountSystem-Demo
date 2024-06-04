#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QWidget>
#include <fstream>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include "Account/Encryptable/Encryptable.h"
#include "Account/basicAccount.h"
using bms::BasicAccount;
#include"forgotpwd.h"

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
        QMessageBox::information(this,"Title","手机号不能为空");
        return;
    }
    if (id.isEmpty()) {
        QMessageBox::information(this,"Title","身份证号不能为空");
        return;
    }
    if (name.isEmpty()) {
        QMessageBox::information(this,"Title","姓名不能为空");
        return;
    }
    if (passwd != ui->passwdConfirm->text()) {
        QMessageBox::information(this,"Title","两次密码输入不一致");
        return;
    }
    // 检查密码强度
    if (!checkPasswdStrength(passwd)) {
        QMessageBox::information(this,"Title","密码强度不足：至少需要8位，包含大小写字母和数字");
        return;
    }
    BasicAccount account(name.toStdString(), passwd.toStdString(), phone.toStdString(), id.toStdString());
    account.store(account.datafile());
        QMessageBox::information(this,"Title","注册成功！");
}

void MainWindow::login_click() {
    // 如果用于注册的输入框显示，则隐藏
    if (ui->idEdit->isVisible()) {
        ui->idEdit->hide();
        ui->nameEdit->hide();
        ui->passwdConfirm->hide();
        return;
    }
    // 获取用户输入的账号和密码
    QString phone = ui->phoneEdit->text();
    QString password = ui->passwdEdit->text();

    BasicAccount user(phone.toStdString(), ".");
    // 拼接用户信息文件的路径
    std::string filename = user.datafile();

    /*
     * 以下代码用于测试登录功能
    */
        //  // qml引擎
        // QQmlApplicationEngine* engine = new QQmlApplicationEngine;
        // // 加载qml文件
        // engine->rootContext()->setContextProperty("user", user);
        // engine->load(QUrl(QStringLiteral("qrc:/qml/dashboard.qml")));

    std::ifstream file(filename);

    if (file.good()) {
        // 文件存在，读取用户信息
        BasicAccount* existUser = new BasicAccount();
        existUser->load(filename);
        // 比对密码
        if (existUser->passwd().toStdString() != bms::Encryptable::hashSHA256(password.toStdString())) {
            QMessageBox::information(this,"Title", "登录失败，请检查手机号和密码是否正确");
            return;
        }

        // qml引擎
        QQmlApplicationEngine* engine = new QQmlApplicationEngine;
        // 加载qml文件
        engine->rootContext()->setContextProperty("user", existUser);
        engine->load(QUrl(QStringLiteral("qrc:/qml/dashboard.qml")));
    } else {
        // 文件不存在，登录失败
        QMessageBox::information(this,"Title", "登录失败，请检查手机号和密码是否正确");
    }

}

void MainWindow::on_clear_button_clicked()
{
    ui->nameEdit->clear();
    ui->idEdit->clear();
    ui->phoneEdit->clear();
    ui->passwdEdit->clear();
    ui->passwdConfirm->clear();
}


void MainWindow::on_fogotpw_clicked()
{
    this->hide();
    next=new forgotpwd;
    next->show();
}

