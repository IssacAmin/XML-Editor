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
    string mostActive ="The Most Active User: "+  most_active();
    ui->textBrowser->setText(QString::fromStdString(mostActive));

}

//Most influencer users
void networkWindow::on_pushButton_16_clicked()
{
    string mostActive ="The Most Influencer User: "+  most_influencer();
    ui->textBrowser->setText(QString::fromStdString(mostActive));
}

//follow suggestions
void networkWindow::on_pushButton_17_clicked()
{
    string user1 = ui->lineEdit_2->text().toStdString();
    if(user1 != "")
    {
        vector<string> suggestions;
        suggestions = suggest(user1);
        bool done = false;
        int size = (int) suggestions.size();
        if(size == 1)
        {
            if(strcmp(suggestions[0].c_str(),"user not found") == 0)
            {
                done = true;
                QMessageBox::warning(this, "title","user not found");
            }
        }
        if(!done)
        {
            string msg = "Suggestions: \n";
            for(int i = 0;i < size;i++)
            {
                msg += (suggestions[i]+"\n");
            }
            ui->textBrowser->setText(QString::fromStdString(msg));
        }
    }
    else
    {
        QMessageBox::warning(this, "title", "Enter a name in user 1 field");
    }
}

// //mutual
void networkWindow::on_pushButton_14_clicked()
{
    string user1 = ui->lineEdit_2->text().toStdString();
    string user2 = ui->lineEdit_3->text().toStdString();
    if(user1 != "" && user2 != "")
    {

        vector<string> common;
        common = common_users(user1, user2);
        bool done = false;
        int size = (int) common.size();
        if(size == 1)
        {
            if(strcmp(common[0].c_str(),"user 1 or user 2 are not found") == 0)
            {
                done = true;
                QMessageBox::warning(this, "title","user 1 or user 2 are not found");
            }
        }
        if(!done)
        {
            string msg = "Common Users: \n";
            for(int i = 0;i < size;i++)
            {
                msg += (common[i]+"\n");
            }
            ui->textBrowser->setText(QString::fromStdString(msg));
        }

    }
    else
    {
        QMessageBox::warning(this, "title", "Enter a name in user 1 and 2 fields");
    }

}
