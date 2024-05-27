#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QFile>
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class Sign_up;
}

class Sign_up : public QWidget {
    Q_OBJECT

public:
    explicit Sign_up(QWidget *parent = nullptr);
    ~Sign_up();

private slots:
    void on_clearButton_clicked();  // 清除按钮

    void on_cancelButton_clicked();  // 取消按钮，即返回最初登陆界面

    void on_sureButton_clicked();  // 确定按钮，保存注册信息到文件
private:
    Ui::Sign_up *ui;
};

#endif  // SIGN_UP_H
