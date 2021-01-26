/*
Project   : Student Management System
     Group: G1 - Group 8
Leader #1 : Hossain, Mohammad Mubdiul
       ID : 1161303847
Member #2 : Khaleduzzaman
       ID : 1171300038
  Tutorial: TT01
  Lecturer: Sharaf Eldeen Sami Mohammed Al Horani
*/
#include "logIndialog.h" //login menu's header
#include <QApplication>  //QApplication header
#include "mainmenu.h"    //Custom built MainMenu Header

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    logInDialog login; // login Dialog object
    MainMenu menu;     // Main Menu object
    //connecting login and main menu. login dialog will send a signal to mainmenu which contains
    //login credentials. Mainmenu verifies it and send another signal which cotains true or false.
    //More specifcally if user credentials are ok it will send true and hide login window.
    //if false its shows error
    QObject::connect(&login, SIGNAL(logInData(QString,QString)), &menu, SLOT(logInData(QString,QString)));
    QObject::connect(&menu, SIGNAL(sendData(bool)), &login, SLOT(receiveData(bool)));
    QObject::connect(&menu, SIGNAL(buttonClicked()), &login, SLOT(show()));
    //setting some titles for the windows
    menu.setWindowTitle("Student Management System");
    login.setWindowTitle("Log In");
    login.show(); //showing login dialog first. and mainmenu is by default is hidden.
    //menu.show();
    return a.exec();
}

