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
    explicit forgotpwd(QWidget* mainWindo = nullptr, QWidget *parent = nullptr);
    ~forgotpwd();


private slots:
    void pushButton_clicked();

    void backBtn_clicked();

private:
    Ui::forgotpwd *ui;
    QWidget* mainWindow;
};

#endif  // FORGOTPWD_H
