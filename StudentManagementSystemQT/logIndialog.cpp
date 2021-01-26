#include "logIndialog.h"
#include "ui_logIndialog.h"
#include <QMessageBox>

logInDialog::logInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logInDialog)
{
    ui->setupUi(this);
}

logInDialog::~logInDialog()
{
    delete ui;
}
void logInDialog::on_pushButton_2_clicked()
{
    QApplication::quit(); //closing program
}
void logInDialog::on_loginButton_clicked()
{
    QString userName;
    QString password;
    userName = ui->text_box_ID->text(); //setting entered user id to userName
    password = ui->text_box_Password->text();//setting entered user password to password
    emit logInData(userName, password); //emitting a signal to main menu class to transfer username and password
    if(istrue) //checking the login data is true or false
    {
        ui->text_box_ID->clear();
        ui->text_box_Password->clear();
        ui->showerror->clear();
        this->close(); //hiding logInDialog
        //hide();
    }
    else
    {
        ui->showerror->setText("Invalid ID or Password"); //error showing if log in data incorrect
    }
}
void logInDialog::receiveData(bool istrue) //receiving true false value if login data ok or not
{
    this->istrue=istrue;
}
