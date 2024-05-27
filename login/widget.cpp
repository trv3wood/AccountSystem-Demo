#include "widget.h"
#include "./ui_widget.h"
#include "mainwindow.h" // 包含主界面头文件

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置 statusLabel 文本和可见性
    ui->statusLabel->setText("Ready");
    ui->statusLabel->setVisible(false); // 初始时设置为不可见

    // 连接登录按钮点击信号到槽函数
    connect(ui->loginButton, &QPushButton::clicked, this, &Widget::on_loginButton_clicked);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_loginButton_clicked()
{
    // 获取用户输入的账号和密码
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // 拼接用户信息文件的路径
    QString filePath = "C:\\Users\\wwh\\Desktop\\user\\" + username+".txt";

    // 检查文件是否存在
    QFile file(filePath);
    if (file.exists()) {
        // 文件存在，尝试读取用户信息
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream into(&file);
            QString storedUsername = into.readLine().trimmed(); // 读取文件中的用户名
            QString storedPassword = into.readLine().trimmed(); // 读取文件中的密码
            file.close();

            // 验证账号密码是否匹配
            if (username == storedUsername && password == storedPassword) {
                // 登录成功，进入主界面
                this->hide();
                MainWindow *mainWindow = new MainWindow;
                mainWindow->show();
            }
            else {
                // 账号或密码不匹配，登录失败
                ui->statusLabel->setText("账号或密码错误！");
            }
        }
        else {
            // 无法打开文件，登录失败
            ui->statusLabel->setText("无法打开用户信息文件！");
        }
    } else {
        // 文件不存在，登录失败
        ui->statusLabel->setText("账号或密码错误！");
    }

}
