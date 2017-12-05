#include "managersys.h"
#include "ui_managersys.h"

ManagerSys::ManagerSys(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerSys)
{
    ui->setupUi(this);
}

ManagerSys::~ManagerSys()
{
    delete ui;
}
