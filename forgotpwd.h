#ifndef FORGOTPWD_H
#define FORGOTPWD_H

#include <QPushButton>
#include <QQmlApplicationEngine>
#include <QWidget>

namespace Ui {
class forgotpwd;
}

class forgotpwd : public QWidget {
    Q_OBJECT

public:
    explicit forgotpwd(QWidget* mainWindow = nullptr,
                       QWidget* parent = nullptr);
    ~forgotpwd();

private slots:
    void pushButton_clicked();

    void backBtn_clicked();

private:
    Ui::forgotpwd* ui;
    QWidget* mainWindow;
};

#endif  // FORGOTPWD_H
