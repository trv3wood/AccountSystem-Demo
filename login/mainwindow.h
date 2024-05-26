#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_depositButton_clicked();

    void on_withdrawButton_clicked();

    void on_transferButton_clicked();

    void on_transactionButton_clicked();

    void on_personalButton_clicked();

    void on_on_logoutButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
