#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QListWidget>
#include <QStandardItemModel>
#include <QMessageBox>
//#include <QSqlDatabase>
//#include <QtSql/QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlError>
#include "User.h"
#include "Admin.h"
#include "UnderGraduate.h"
#include "PostGraduate.h"
#include "Diploma.h"
#include <vector>
#include <string>
#include "Faculty.h"
#include "Trimester.h"
#include "Trimester1.h"
#include "Trimester2.h"
#include "Trimester3.h"
#include "Course.h"
#include "UnderGraduateCourse.h"
#include "PostGraduateCourse.h"
#include "DiplomaCourse.h"
#include <QDebug>
#include "delegatecombobox.h"
#include "noteditabledelegate.h"
#include "postgresdatabase.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);

    ~MainMenu();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item); //selecting current item to show respective menu
    void on_logOutButton_clicked();//logout button
    void on_addTrimesterButtonOk_clicked();//admin menu operation when add trimester button is pressed
    void on_currentTrimesterSelected_clicked();//admin menu button operation to set current trimester
    void on_setAvailabilityOk_clicked();//admin menu operation set availability when button pressed
    void on_createFacultyButton_clicked();//admin menu create faculty button operation
    void on_createUserButton_clicked();//admin menu create user button operation
    void on_editNamePageChangeName_clicked();//admin menu change name menu button operation
    void on_editUserComboBox_activated(const QString &arg1);//admin menu change information type seelection
    void on_editGenderPageChangeGender_clicked();//admin menu change gender menu button operation
    void on_editUserFacultyButtonOK_clicked();//admin menu change faculty menu button operation
    void on_enrollButton_clicked();//student menu enrollment button operation
    void on_shpwCoursesTrimesterCbox_activated(const QString &arg1);//student menu show course when trimester combo box activated
    void on_courseRegisterOkButton_clicked();//student menu register button operation
    void on_dropCourseDelete_clicked();//student menu drop button operation
    void on_acadSelectTrimesterComboBox_activated(const QString &arg1);//academician menu select trimester combo box
    void on_acadAddCourseAddButton_clicked();//academician menu add course button operation
    void on_acadEditSelectTrimesterComboBox_activated(const QString &arg1);//academician menu edit selected trimester's courses
    void on_acadEditCourseButton_clicked();//academician menu edit course operation
    void on_acadDeleteTrimesterComboBox_activated(const QString &arg1);//academician menu delete course operation
    void on_acadDeleteButton_clicked();//academician menu delete course button operation
    void on_acadAllCoursesComboBox_activated(const QString &arg1);//academician menu view all course select
    void on_acadAllFacultyComboBox_activated(const QString &arg1);//academician menu view all course select faculty
    void on_acadAllTrimesterComboBox_activated(const QString &arg1);//academician menu view all course select trimester
    void on_profile_triggered();//user view profile
    void on_exit_triggered();//exit

public slots:
    void logInData(QString,QString);//slot to get user id and password from login dialog
signals:
    void sendData(bool);//signal send if the login information correct or wrong
    void buttonClicked();//logout button signal
private:
    bool getAllDataFromServer();//to get all information from server
    bool getCurrentLoggedInUser();//to get current user
    void addWidgetMenuForStudent();//setting up menu for student
    void addWidgetMenuForAdmin();//setting up menu for admin
    void addWidgetMenuForAcademician();//setting up menu for academician
    void adminMenuCurrentTrimester();//setting up admin menu for current trimester
    void adminMenuAddTrimester();//setting up admin menu to add trimester
    void modelViewAddClass();//setting up table for admin menu add class
    void setAvailabilty();//setting up admin menu to set availability
    void addFacultyMenu();//setting up admin menu to add faculty
    void adminAddUser();//setting up admin menu to add user
    void adminEditUser();//setting up admin menu to edit user
    void studentMenuEnroll();//setting up student menu to enroll
    void studentMenuViewCourse();//setting up student menu to view course
    void viewStudentCourseTable(const QString&);//student menu to view courses
    void courseRegisterMenu();//student menu course register.
    void courseDeleteMenu();//student menu course drop.
    void acadViewCourseMenu();//academician menu course view.
    QStandardItemModel* acadViewCourseTable(const QString&); //academician menu course table view.
    void acadAddCourse();//academician menu add course setting
    void acadEditCourse();//academician menu edit course setting
    void acadDeleteCourse();//academician menu delete course setting
    void acadViewAllCourseAndStudent();//academician menu view all course and its student setting
    Ui::MainMenu *ui; //declaring ui
    QStandardItemModel *model; //table model for courses
    std::vector<Faculty*> faculty;//faculty container
    std::vector<Trimester*> trimester;//trimester container

    QString userID;
    QString password;
    QString registrationAvailableTrimester;

    Admin *admin; //declaring admin pointer
    User *currentLoggedInUser; //declaring current logged in user pointer
    Academician* academician; //declaring academician pointer

    User* editableUser; //editable user for admin edit user declaration
    Student* student; //declaring student pointer

    bool databaseIsOK; //bool for database is connected or not
    PostgresDatabase *database;

    std::string acadademecianEditCourseChosenTrimester;//choosen trimester string to edit courses for that trimester
    std::string academecianDeleteCourseChoosenTrimester;//choosen trimester string to edit courses for that trimester

    std::string viewAllSelectedFaculty; //choosen faculty to show courses and students
    std::string viewAllSelectedTrimester;//choosen trimester to show courses and students

    QString upcomingTrimester; //upcoming trimester string
    QString currentTrimester;//current trimester string
};

#endif // STUDENTMENU_H
