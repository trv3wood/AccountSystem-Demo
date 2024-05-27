#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void signup_click();
    void login_click();

// private slots:
//     void on_sign_up_clicked();

    void on_clear_button_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
