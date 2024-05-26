#include "sign_up.h"

#include "loginwindow.h"
#include "ui_sign_up.h"
// #include "accountonly.h"//进入登录之后的主界面那个的头函数

Sign_up::Sign_up(QWidget *parent) : QWidget(parent), ui(new Ui::Sign_up) {
    ui->setupUi(this);
}

Sign_up::~Sign_up() { delete ui; }

// 清除
void Sign_up::on_clearButton_clicked() {
    ui->name_edit->clear();
    ui->identity_edit->clear();
    ui->tpnumber_edit->clear();
    ui->passwd_edit->clear();
    ui->passwdconfirm_edit->clear();
}

// 取消，即后退
void Sign_up::on_cancelButton_clicked() {
    this->close();
    MainWindow *w = new MainWindow;
    w->show();
}

// 确定
void Sign_up::on_sureButton_clicked() {
    QString name = ui->name_edit->text();
    QString identitynumber = ui->identity_edit->text();
    QString telephonenumber = ui->tpnumber_edit->text();
    QString passwd = ui->passwd_edit->text();
    QString passwdcon = ui->passwdconfirm_edit->text();
    QString d = " ";

    if (passwd != passwdcon) {
        QMessageBox::warning(this, "warning",
                             "两遍密码输入不一样，请重新设置密码！");
    } else {
        if (name != nullptr && identitynumber != nullptr &&
            telephonenumber != nullptr && passwd != nullptr) {
            QFile file(name);
            file.open(QIODevice::WriteOnly);
            QByteArray ba;
            ba.append(name.toUtf8());
            ba.append(d.toUtf8());
            ba.append(identitynumber.toUtf8());
            ba.append(d.toUtf8());
            ba.append(telephonenumber.toUtf8());
            ba.append(d.toUtf8());
            ba.append(passwd.toUtf8());

            file.write(ba);
            file.flush();
            file.close();

            this->hide();
            // accountonly*a=new accountonly;
            // a->show();
        }
    }
}
