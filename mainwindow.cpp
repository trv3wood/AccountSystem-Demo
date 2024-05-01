#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->vLayoutButton->setAlignment(Qt::AlignCenter);
    // 创建阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setXOffset(5);
    shadow->setYOffset(5);

    ui->buttonLogin->setGraphicsEffect(shadow);
    ui->buttonSignUp->setGraphicsEffect(shadow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

