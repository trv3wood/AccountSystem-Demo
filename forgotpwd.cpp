#include "forgotpwd.h"
#include <qmessagebox.h>
#include <qobject.h>
#include <QMessageBox>

#include <QFile>
#include <QString>

#include "Account/basicAccount.h"
#include "ui_forgotpwd.h"

forgotpwd::forgotpwd(QWidget* prev, QWidget* parent)
    : QWidget(parent), ui(new Ui::forgotpwd), mainWindow(prev) {
    ui->setupUi(this);
    QObject::connect(ui->backBtn, SIGNAL(clicked(bool)), this,
                     SLOT(backBtn_clicked()));
    QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), this,
                     SLOT(pushButton_clicked()));
    // 居中
    ui->phonenum->setAlignment(Qt::AlignCenter);
    ui->passwd->setAlignment(Qt::AlignCenter);
    ui->phonenum->setPlaceholderText("请输入手机号");
    ui->passwd->setPlaceholderText("请输入新密码");
}

forgotpwd::~forgotpwd() { delete ui; }

void forgotpwd::pushButton_clicked() {
    bms::BasicAccount user(ui->phonenum->text().toStdString(), ".");
    QString filename = QString::fromStdString(user.datafile());
    QFile outfile(filename);
    if (outfile.exists()) {
        user.load();
        user.setPasswd(ui->passwd->text().toStdString());
        user.store();
        outfile.close();
        QMessageBox::information(this, "Success", "密码修改成功！");
    } else {
        QMessageBox::warning(this, "Warning", "未找到该用户！");
    }
}

void forgotpwd::backBtn_clicked() {
    mainWindow->show();
    this->hide();
}
