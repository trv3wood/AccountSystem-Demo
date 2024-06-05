#include "forgotpwd.h"
#include<QString>
#include<QFile>
#include "Account/basicAccount.h"

#include "ui_forgotpwd.h"

forgotpwd::forgotpwd(QWidget *parent) : QWidget(parent), ui(new Ui::forgotpwd) {
    ui->setupUi(this);
}

forgotpwd::~forgotpwd() { delete ui; }

std::string forgotpwd::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

void forgotpwd::on_pushButton_clicked()
{
    QString filename=ui->phonenum->text()+".dat";
    QFile outfile(filename);
    if(outfile.exists())
    {
        ui->exist->setText("账号存在");
        bms::BasicAccount a;
        std::string newname=q2s(filename);
        a.load(newname);
        std::string psw=q2s(ui->passwd->text());
        a.setPasswd(psw);
        a.store(newname);
        outfile.close();

//        QQmlApplicationEngine engine;
//        forgotpwd forgotPwd;

//        engine.rootContext()->setContextProperty("forgotpwd", &controller);
//        engine.load(QUrl(QStringLiteral("qrc:/qml/dashboard.qml")));

    }
    else
    {
        ui->exist->setText("账户不存在");
    }
}

