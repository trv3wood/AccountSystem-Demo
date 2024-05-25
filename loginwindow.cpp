#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include <QGraphicsEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sign_up_clicked()
{
    this->hide();
    Sign_up*x=new Sign_up;//打开注册的窗口
    x->show();
}

