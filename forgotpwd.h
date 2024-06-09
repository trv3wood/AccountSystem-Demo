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
    Ui::forgotpwd* ui;

private slots:
    void pushButton_clicked();

    void backBtn_clicked();

private:
    QWidget* mainWindow;
};

#endif  // FORGOTPWD_H
