#ifndef FORGOTPWD_H
#define FORGOTPWD_H

#include <QWidget>

namespace Ui {
class forgotpwd;
}

class forgotpwd : public QWidget {
    Q_OBJECT

public:
    explicit forgotpwd(QWidget *parent = nullptr);
    ~forgotpwd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::forgotpwd *ui;
};

#endif  // FORGOTPWD_H
