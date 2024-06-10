#include "loginwindow.h"

#include <QGraphicsEffect>
#include <QMessageBox>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWidget>
#include <QtQuick/QQuickView>
#include <fstream>

#include "./ui_loginwindow.h"
#include "Account/Encryptable/Encryptable.h"
#include "Account/PremiumAccount.h"
#include "Account/basicaccount.h"
#include "ui_forgotpwd.h"

using bms::BasicAccount, bms::PremiumAccount;
#include "forgotpwd.h"
#include "sourchange.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
    ui->idEdit->hide();
    ui->nameEdit->hide();
    ui->passwdConfirm->hide();

    QObject::connect(ui->sign_up_btn, SIGNAL(clicked()), this,
                     SLOT(signup_click()));
    QObject::connect(ui->loginBtn, SIGNAL(clicked()), this,
                     SLOT(login_click()));
    QObject::connect(ui->clear_button, SIGNAL(clicked()), this,
                     SLOT(clear_button_click()));
    QObject::connect(ui->fogotpwBtn, SIGNAL(clicked()), this,
                     SLOT(fogotpw_click()));
}

MainWindow::~MainWindow() { delete ui; }

static bool isStrongPasswd(const QString &passwd) {
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
        QMessageBox::information(this, "Title", "手机号不能为空");
        return;
    }
    if (id.isEmpty()) {
        QMessageBox::information(this, "Title", "身份证号不能为空");
        return;
    }
    if (name.isEmpty()) {
        QMessageBox::information(this, "Title", "姓名不能为空");
        return;
    }
    if (passwd != ui->passwdConfirm->text()) {
        QMessageBox::information(this, "Title", "两次密码输入不一致");
        return;
    }
    // 检查密码强度
    if (!isStrongPasswd(passwd)) {
        QMessageBox::information(
            this, "Title", "密码强度不足：至少需要8位，包含大小写字母和数字");
        return;
    }
    BasicAccount account(name.toStdString(), passwd.toStdString(),
                         phone.toStdString(), id.toStdString());
    account.store();
    QMessageBox::information(this, "Title", "注册成功！");
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
    // QString phone = "18823231622";
    // QString password = "Ricky4881";

    // 判断是否为高级用户
    BasicAccount *user = nullptr;
    if (PremiumAccount::isPremium(phone)) {
        user = new PremiumAccount(phone.toStdString(), ".");
    } else {
        user = new BasicAccount(phone.toStdString(), ".");
    }
    // 拼接用户信息文件的路径
    std::string filename = user->datafile();

    std::ifstream file(filename);

    if (file.good()) {
        // 文件存在，读取用户信息
        user->load();
        // 比对密码
        if (user->passwd().toStdString() !=
            bms::Encryptable::hashSHA256(password.toStdString())) {
            QMessageBox::information(this, __FUNCTION__,
                                     "登录失败，请检查手机号和密码是否正确");
            delete user;
            return;
        }
        // QML engine setup
        QQmlApplicationEngine *engine = new QQmlApplicationEngine;
        if (!engine) {
            QMessageBox::information(this, __FUNCTION__, "QML引擎初始化失败");
            delete user;
            return;
        }

        engine->rootContext()->setContextProperty("user", user);

        const QUrl url(QStringLiteral("qrc:/qml/dashboard.qml"));
        QObject::connect(
            engine, &QQmlApplicationEngine::objectCreated, this,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl) QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);

        // 注册 Sourchange 类到 QML
        qmlRegisterType<Sourchange>("Sourchange", 1, 0, "Sourchange");

        engine->load(url);

        if (engine->rootObjects().isEmpty()) {
            QMessageBox::information(this, __FUNCTION__, "加载QML文件失败");
            delete user;
            delete engine;
            return;
        }
    } else {
        // 文件不存在，登录失败
        QMessageBox::information(this, __FUNCTION__,
                                 "登录失败，请检查手机号和密码是否正确");
        delete user;
        return;
    }
}

void MainWindow::clear_button_click() {
    ui->nameEdit->clear();
    ui->idEdit->clear();
    ui->phoneEdit->clear();
    ui->passwdEdit->clear();
    ui->passwdConfirm->clear();
}

void MainWindow::fogotpw_click() {
    forgotpwd *changePasswd = new forgotpwd(this);
    changePasswd->show();
    this->hide();
}

// 用于连接qml中修改密码的
void MainWindow::cppConnection() {
    forgotpwd *changePasswd = new forgotpwd;
    changePasswd->show();
    changePasswd->ui->backBtn->hide();
}
