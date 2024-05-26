#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widget.h"
#include "./ui_widget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // 连接主界面各个功能按钮的点击信号到对应的槽函数
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::on_withdrawButton_clicked);
    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::on_depositButton_clicked);
    connect(ui->transferButton, &QPushButton::clicked, this, &MainWindow::on_transferButton_clicked);
    connect(ui->transactionButton, &QPushButton::clicked, this, &MainWindow::on_transactionButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_depositButton_clicked()
{
    //存钱
}


void MainWindow::on_withdrawButton_clicked()
{
    //取钱
}


void MainWindow::on_transferButton_clicked()
{
    //转账
}


void MainWindow::on_transactionButton_clicked()
{
    //查询
}


void MainWindow::on_personalButton_clicked()
{
    //查询个人信息
}


void MainWindow::on_on_logoutButton_clicked()
{
    // 处理退出登录逻辑，返回到登录界面
    this->hide();
    Widget *w=new Widget;
    w->show();
}

