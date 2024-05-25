#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>

#include"sign_up.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
// protected:
    // void resizeEvent(QResizeEvent* event) override {
    //     // 调用基类的 resizeEvent
    //     QWidget::resizeEvent(event);

    //     // 获取新的宽度和高度
    //     int width = event->size().width();
    //     int height = event->size().height();

    //     // 打印新的大小到控制台
    //     qDebug() << "New size:" << width << "x" << height;
    // }
private slots:
    void on_sign_up_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
