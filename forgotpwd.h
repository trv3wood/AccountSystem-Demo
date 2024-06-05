#ifndef FORGOTPWD_H
#define FORGOTPWD_H

#include <QWidget>
#include<QPushButton>
#include <QQmlApplicationEngine>

namespace Ui {
class forgotpwd;
}

class forgotpwd : public QWidget {
    Q_OBJECT

public:
    explicit forgotpwd(QWidget *parent = nullptr);
    ~forgotpwd();
    std::string q2s(const QString &s);

//public slots:
//    void callcpp_clicked(){
//        on_pushButton_clicked();
//    }
private slots:
    void on_pushButton_clicked();

private:
    Ui::forgotpwd *ui;
};

#endif  // FORGOTPWD_H
