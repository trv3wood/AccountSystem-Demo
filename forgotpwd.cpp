#include "forgotpwd.h"
#include<QString>
#include<QFile>
#include "Account/basicAccount.h"

#include "ui_forgotpwd.h"

forgotpwd::forgotpwd(QWidget *parent) : QWidget(parent), ui(new Ui::forgotpwd) {
    ui->setupUi(this);
}

forgotpwd::~forgotpwd() { delete ui; }


void forgotpwd::on_pushButton_clicked()
{
    bms::BasicAccount user(ui->phonenum->text().toStdString(), ".");
    QString filename = QString::fromStdString(user.datafile());
    QFile outfile(filename);
    if(outfile.exists())
    {
        ui->exist->setText("账号存在");
        user.load(user.datafile());
        user.setPasswd(ui->passwd->text().toStdString());
        user.store(user.datafile());
        outfile.close();
    }
    else
    {
        ui->exist->setText("账户不存在");
    }
}

