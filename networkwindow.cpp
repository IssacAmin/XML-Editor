#include "networkwindow.h"
#include "ui_networkwindow.h"

networkWindow::networkWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::networkWindow)
{
    ui->setupUi(this);
}

networkWindow::~networkWindow()
{
    delete ui;
}


//Most active User
void networkWindow::on_pushButton_15_clicked()
{

}



//Most influencer users
void networkWindow::on_pushButton_16_clicked()
{

}

//follow suggestions
void networkWindow::on_pushButton_17_clicked()
{

}

//mutual
void networkWindow::on_pushButton_14_clicked()
{

}

