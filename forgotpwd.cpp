#include "forgotpwd.h"

#include <QFile>
#include <QString>

#include "Account/basicAccount.h"
#include "ui_forgotpwd.h"

forgotpwd::forgotpwd(QWidget* prev, QWidget *parent) : QWidget(parent), ui(new Ui::forgotpwd), mainWindow(prev) {
    ui->setupUi(this);
    QObject::connect(ui->backBtn, SIGNAL(clicked(bool)), this, SLOT(backBtn_clicked()));
}

forgotpwd::~forgotpwd() { delete ui; }

void forgotpwd::pushButton_clicked() {
    bms::BasicAccount user(ui->phonenum->text().toStdString(), ".");
    QString filename = QString::fromStdString(user.datafile());
    QFile outfile(filename);
    if (outfile.exists()) {
        ui->exist->setText("账号存在");
        user.load(user.datafile());
        user.setPasswd(ui->passwd->text().toStdString());
        user.store(user.datafile());
        outfile.close();
    } else {
        ui->exist->setText("账户不存在");
    }
}

void forgotpwd::backBtn_clicked()
{
    mainWindow->show();
    this->hide();
}

