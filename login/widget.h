#ifndef WIDGET_H
#define WIDGET_H
#include "mainwindow.h"

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QIODevice>
#include <QLabel>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_loginButton_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
