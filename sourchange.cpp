#include "sourchange.h"
#include"loginwindow.h"

Sourchange::Sourchange(QObject *parent) : QObject(parent)
{

}
void Sourchange::cppSlot(){
    MainWindow*m=new MainWindow;
    m->cppConnection();
}
