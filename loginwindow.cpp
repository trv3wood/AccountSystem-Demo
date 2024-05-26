#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include <QGraphicsEffect>
#include <QObject>
#include <QLabel>

#include "Account/basicAccount.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->sign_up_btn, SIGNAL(clicked()), this, SLOT(signup()));
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

void MainWindow::signup() {
    QString id = ui->idInput->text();
    QString passwd = ui->passwdInput->text();
    if (id.isEmpty() || passwd.isEmpty()) {
        QWidget *widget = new QWidget();
        widget->setWindowTitle("Error");
        widget->resize(400, 300);
        QLabel *label = new QLabel(widget);
        label->resize(400, 300);
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        label->setText("ID或密码为空");
        widget->show();
        return;
    }
    // 检查密码强度
    if (!checkPasswdStrength(passwd)) {
        QWidget *widget = new QWidget();
        widget->setWindowTitle("Error");
        widget->resize(400, 300);
        QLabel *label = new QLabel(widget);
        label->resize(400, 300);
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        label->setText("密码强度太弱");
        widget->show();
        return;
    }
    bms::BasicAccount account("name", passwd.toStdString(), "nowhere", id.toStdString());
    account.store(account.datafile());
}
