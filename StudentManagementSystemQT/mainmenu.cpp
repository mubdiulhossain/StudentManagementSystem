#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QListWidget>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    hide(); //Hiding Mainmenu So that only login Dialog is showed first
    userID="";
    password="";
    database = new PostgresDatabase("localhost", "StudentManagementSystem", "Postgres", "rakin1234", 5432);
    //databaseIsOK = getAllDataFromServer(); //initially getting all data from server/database
    connect(ui->addTrimesterLineEdit, SIGNAL(returnPressed()),ui->addTrimesterButtonOk,SIGNAL(clicked())); //Connect to on Push button Ok from add trimester edit line when pressed enter
}
MainMenu::~MainMenu()
{
    delete ui;
}
bool MainMenu::getCurrentLoggedInUser()
{
    //comparing user id and password to admin if yes then...
    if(admin->getUserID().compare(userID.toUtf8().constData())==0&&admin->checkPassword(password.toUtf8().constData()))
    {
        currentLoggedInUser = admin;//...current logged in user will be set to admin's pointer
        return true;
    }
    else
    {
        if(faculty.size()!=0) //checking if there is no faculty
        {
            for(unsigned int i = 0; i<faculty.size();i++)
            {
                for(unsigned int j = 0;j<faculty[i]->getAcademician().size();j++) //checking all the academician in all faculty
                {
                    if(faculty[i]->getAcademician()[j]->getUserID().compare(userID.toUtf8().constData())==0&&faculty[i]->getAcademician()[j]->checkPassword(password.toUtf8().constData())) //comparing academicians user id and password with entered id and password
                    {
                        currentLoggedInUser = faculty[i]->getAcademician()[j]; //if found the pointer location is assigned to current logged in user
                        return true;
                    }
                }
                for(unsigned int j = 0;j<faculty[i]->getStudent().size();j++)
                {
                    //same as academcian
                    if(faculty[i]->getStudent()[j]->getUserID().compare(userID.toUtf8().constData())==0&&faculty[i]->getStudent()[j]->checkPassword(password.toUtf8().constData()))
                    {

                        currentLoggedInUser = faculty[i]->getStudent()[j];
                        return true;
                    }
                }
            }
        }
        else
        {
            //if nothing matches log in data is incorrect or user not available
            return false;
        }
    }
    return false;
}
void MainMenu::addWidgetMenuForStudent()
{
    //adding item menu for students
    ui->listWidget->addItem("Enrollment");
    ui->listWidget->addItem("Register Course");
    ui->listWidget->addItem("Drop Course");
    ui->listWidget->addItem("View Course");
    //view course setting
    studentMenuViewCourse();
    ui->stackedWidget->setCurrentWidget(ui->viewCourse);
}
void MainMenu::addWidgetMenuForAdmin()
{
    //adding item menu for admin
    ui->listWidget->addItem("Add Trimester");
    ui->listWidget->addItem("Add User");
    ui->listWidget->addItem("Edit User");
    ui->listWidget->addItem("Add Faculty");
    ui->listWidget->addItem("Set Trimester");
    ui->listWidget->addItem("Set Availabilty for Current or Upcoming Trimesters");
    ui->listWidget->addItem("View Courses and Students");
    //setting current widget as add trimester menu
    ui->stackedWidget->setCurrentWidget(ui->addTrimester);
}
void MainMenu::addWidgetMenuForAcademician()
{
    //same as others
    ui->listWidget->addItem("View Your Courses");
    ui->listWidget->addItem("Add Course");
    ui->listWidget->addItem("Delete Course");
    ui->listWidget->addItem("Edit Course");
    ui->listWidget->addItem("All Courses And Students");
    acadViewCourseMenu();
    ui->stackedWidget->setCurrentWidget(ui->viewAcadCourses);
}
void MainMenu::logInData(QString userID, QString password)
{
    //recieved user id and passwords from logInDialog
    this->userID=userID;
    this->password=password;

    bool isSuc=false;
    if(database->databaseOpen()) //checkin database got all the data from server
    {
        currentLoggedInUser = database->getUser(userID, password); //getting current logged in user and checking credentials
        if(currentLoggedInUser!=nullptr)
        {
            isSuc=true;
            if(currentLoggedInUser->getUserGender()=='m') //checking if the user is male
            {
                ui->welcomeText->setText("Welcome Mr. "+QString::fromStdString(currentLoggedInUser->getUserName()));
            }
            else
            {
                if((currentLoggedInUser->getUserGender()=='f'))//checking if the user is female
                {
                    ui->welcomeText->setText("Welcome Ms. "+QString::fromStdString(currentLoggedInUser->getUserName()));
                }
                else
                {
                    ui->welcomeText->setText("Welcome "+QString::fromStdString(currentLoggedInUser->getUserName()));
                }
            }
            //checking current logged in user is an admin
            admin = dynamic_cast<Admin*>(currentLoggedInUser);
            if(admin!=nullptr)
            {
                //if yes setting up current ui for admin
                ui->listWidget->clear();
                ui->currentTrimesterLabel->setText("Current Trimester: "+currentTrimester+", Upcoming Trimester: "+upcomingTrimester);
                addWidgetMenuForAdmin();
            }
            else
            {
                //checking current logged in user is an academician
                academician = dynamic_cast<Academician*>(currentLoggedInUser);
                if(academician!=nullptr)
                {
                    //if yes setting up current ui for academician
                    ui->listWidget->clear();
                    addWidgetMenuForAcademician();
                    ui->currentTrimesterLabel->setText("Current Trimester: "+currentTrimester+", Upcoming Trimester: "+upcomingTrimester);
                }
                else
                {
                    //same as others
                    student = dynamic_cast<Student*>(currentLoggedInUser);
                    if(student!=nullptr)
                    {
                        ui->listWidget->clear();

                        if(database->databaseOpen()) // after confirming user as Student program will now fetch the data of courses from database
                        {
                            //program will fetch the data for the logged in student
                            QSqlQuery getTrimesterQ("SELECT * FROM \""+QString::fromStdString(student->getUserID())+"trimesterTaken\"");
                            while(getTrimesterQ.next())
                            {
                                if(student->getTakenTrimester().size()==0)
                                {
                                    student->addTrimester(getTrimesterQ.value(0).toString().toUtf8().constData());
                                }
                                else
                                {
                                    int countt=0;
                                    for(unsigned int i = 0; i<student->getTakenTrimester().size();i++)
                                    {
                                        if(student->getTakenTrimester()[i].compare(getTrimesterQ.value(0).toString().toUtf8().constData())==0)
                                        {
                                            countt++;                                            
                                        }
                                    }
                                    if(countt==0)
                                    {
                                        student->addTrimester(getTrimesterQ.value(0).toString().toUtf8().constData());
                                    }
                                }
                            }
                        }
                        db.close();
                        ui->currentTrimesterLabel->setText("Current Trimester: "+currentTrimester+", Upcoming Trimester: "+upcomingTrimester);
                        addWidgetMenuForStudent();
                    }
                }
            }
            //if all ok now program will show main menu
            show();
        }
        else
        {
            isSuc=false;
        }
    }
    else
    {
        //error showing for database not found
        QMessageBox::critical(this,"Error","Connection to database was unsuccessful");
    }
    emit sendData(isSuc); //emitting signal for loging state to LogInDialog
}
void MainMenu::on_listWidget_itemClicked(QListWidgetItem *item)//SelectionMenuSettings
{
    if(item->text()=="Enrollment")
    {
        studentMenuEnroll();
        ui->stackedWidget->setCurrentWidget(ui->enrollmentPage);
    }
    else
    {
        if(item->text()=="Register Course")
        {
            ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : black; }");
            ui->coursesOfferedErrorLabel->clear();
            courseRegisterMenu();
            ui->stackedWidget->setCurrentWidget(ui->registerCoursePage);
        }
        else
        {
            if(item->text()=="Drop Course")
            {
                ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : black; }");
                ui->dropCourseErrorLabel->clear();
                courseDeleteMenu();
                ui->stackedWidget->setCurrentWidget(ui->dropCourse);
            }
            else
            {
                if(item->text()=="View Course")
                {
                    studentMenuViewCourse();
                    ui->stackedWidget->setCurrentWidget(ui->viewCourse);
                }
                else
                {
                    if(item->text()=="Add Trimester")
                    {
                        adminMenuAddTrimester();
                        ui->stackedWidget->setCurrentWidget(ui->addTrimester);

                    }
                    else
                    {
                        if(item->text()=="Add User")
                        {
                            adminAddUser();
                            ui->stackedWidget->setCurrentWidget(ui->addUserFFaculty);
                        }
                        else
                        {
                            if(item->text()=="Add Faculty")
                            {
                                addFacultyMenu();
                                ui->stackedWidget->setCurrentWidget(ui->addFaculty);
                            }
                            else
                            {
                                if(item->text()=="Edit User")
                                {
                                    adminEditUser();
                                    ui->stackedWidget->setCurrentWidget(ui->editUser);
                                }
                                else
                                {
                                    if(item->text()=="View Your Courses")
                                    {
                                        acadViewCourseMenu();
                                        ui->stackedWidget->setCurrentWidget(ui->viewAcadCourses);
                                    }
                                    else
                                    {
                                        if(item->text()=="Set Trimester")
                                        {
                                            adminMenuCurrentTrimester();
                                            ui->stackedWidget->setCurrentWidget(ui->setTrimester);
                                        }
                                        else
                                        {
                                            if(item->text()=="Set Availabilty for Current or Upcoming Trimesters")
                                            {
                                                ui->acadCoursesLabel->clear();
                                                setAvailabilty();
                                                ui->stackedWidget->setCurrentWidget(ui->setAvailabiltyForTrimester);
                                            }
                                            else
                                            {
                                                if(item->text()=="Add Course")
                                                {
                                                    ui->addAcadCourseErrorLabel->clear();
                                                    acadAddCourse();
                                                    ui->stackedWidget->setCurrentWidget(ui->addAcadCourse);
                                                }
                                                else
                                                {
                                                    if(item->text()=="Delete Course")
                                                    {
                                                        ui->acadDeleteErrorShow->clear();
                                                        acadDeleteCourse();
                                                        ui->stackedWidget->setCurrentWidget(ui->deleteAcadCourse);
                                                    }
                                                    else
                                                    {
                                                        if(item->text()=="Edit Course")
                                                        {

                                                            ui->acadEditCourseErrorLabel->clear();
                                                            acadEditCourse();
                                                            ui->stackedWidget->setCurrentWidget(ui->editAcadCourse);
                                                        }
                                                        else
                                                        {
                                                            if(item->text()=="All Courses And Students"||item->text()=="View Courses and Students")
                                                            {
                                                                acadViewAllCourseAndStudent();
                                                                ui->stackedWidget->setCurrentWidget(ui->viewAcadAllCourses);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
bool MainMenu::getAllDataFromServer() //getting datas from server.
{
    bool isOpen = false;
    //Clearing some datas
    currentLoggedInUser = nullptr;
    academician=nullptr;
    student = nullptr;
    editableUser=nullptr;
    acadademecianEditCourseChosenTrimester="";
    academecianDeleteCourseChoosenTrimester="";
    viewAllSelectedFaculty="";
    viewAllSelectedTrimester="";
    upcomingTrimester="";
    currentTrimester="";
    admin = &Admin::getInstance();
    for(unsigned int i=0;i<faculty.size();i++)
    {
        delete faculty[i];
    }
    faculty.clear();
    for(unsigned int i=0;i<trimester.size();i++)
    {
        delete trimester[i];
    }
    trimester.clear();
    isOpen=db.open();
    if(isOpen)
    {
        //Selecting all datas from faculty
        QSqlQuery qryFaculty("SELECT *  FROM \"Faculty\"");
        while(qryFaculty.next())
        {
            Faculty* f = new Faculty(); //creating new faculty object
            f->setFacultyName(qryFaculty.value(0).toString().toUtf8().constData());
            f->setFacultyFullName(qryFaculty.value(1).toString().toUtf8().constData());
            faculty.emplace_back(f);
        }
        //Selecting all datas from user
        QSqlQuery qryUser("SELECT *  FROM \"User\"");
        int countAdmin=0;
        int countUser=0;
        while(qryUser.next())
        {
            countUser++;
            std::string userID, userName, password, facultyName, userType;
            char userGender;
            //assinging value from database
            userID = qryUser.value(0).toString().toUtf8().constData();
            userName = qryUser.value(1).toString().toUtf8().constData();
            password = qryUser.value(2).toString().toUtf8().constData();
            userGender = qryUser.value(3).toString().toUtf8().constData()[0];
            facultyName = qryUser.value(4).toString().toUtf8().constData();
            userType = qryUser.value(5).toString().toUtf8().constData();
            if(userType=="Admin") //checking user type
            {
                countAdmin++;
                if(countAdmin<=1)
                {
                    admin->setUserID(userID);
                    admin->setUserName(userName);
                    admin->setPassword(password);
                    admin->setUserGender(userGender);
                }
                else
                {
                    QMessageBox::critical(this, "Critical Error","More than one Admin found in database, Academician and Student login is prohibited.");
                    return false;
                }
            }
            else
            {
                unsigned int i;
                for(unsigned int k = 0;k<faculty.size();k++)
                {
                    if(facultyName.compare(faculty[k]->getFacultyName())==0)
                    {
                        i=k;
                        break;
                    }
                }
                if(userType=="Academician") //checking user type
                {
                    Academician* u = new Academician(); //creating new academician object
                    //setting academician
                    u->setUserID(userID);
                    u->setUserName(userName);
                    u->setPassword(password);
                    u->setUserGender(userGender);
                    u->setFaculty(faculty[i]);
                    faculty[i]->addAcademician(u);

                }
                else
                {
                    if(userType=="UnderGraduate")
                    {
                        Student* u1 = new UnderGraduate(); //creating new student object as undergraduate
                        //setting Undergraduate student
                        u1->setUserID(userID);
                        u1->setUserName(userName);
                        u1->setPassword(password);
                        u1->setUserGender(userGender);
                        u1->setFaculty(faculty[i]);
                        faculty[i]->addStudent(u1);
                    }
                    else
                    {
                        if(userType=="PostGraduate")
                        {
                            Student* u2 = new PostGraduate(); //creating new student object as postgraduate
                            //setting postgraduate student
                            u2->setUserID(userID);
                            u2->setUserName(userName);
                            u2->setPassword(password);
                            u2->setUserGender(userGender);
                            u2->setFaculty(faculty[i]);
                            faculty[i]->addStudent(u2);

                        }
                        else
                        {
                            if(userType=="Diploma")
                            {
                                Student* u3 = new Diploma(); //creating new student object as diploma
                                //setting diploma student
                                u3->setUserID(userID);
                                u3->setUserName(userName);
                                u3->setPassword(password);
                                u3->setUserGender(userGender);
                                u3->setFaculty(faculty[i]);
                                faculty[i]->addStudent(u3);
                            }
                        }
                    }
                }
            }
        }
        if(countUser==0) // if no user found program will show this error
        {
            QMessageBox::critical(this, "No User Found", "Server doesn't have any user.");
            return false;
        }
        //getting trimester and course data from server
        QSqlQuery qryTrimesters("SELECT *  FROM \"Trimester\""); //Fetching Trimester list from dababase tabale Trimester
        while(qryTrimesters.next())
        {
            QString trmstr = qryTrimesters.value(0).toString(); // assinging trimester attribute to trmstr string which will later be used as Trimester year and search datas(Trimester info table, Courses in that Trimester etc) related to that trimester
            QSqlQuery trmstrNo("SELECT *  FROM \""+trmstr+"\" ORDER BY \"trimesterNo\" ASC"); //if any trimester found program will search for the table created based on that Trimester. which holds the information of that trimester year and how many trimester no is there for that year
            //int countTrmstrNo=0;
            while(trmstrNo.next())
            {
                if(trmstrNo.value(0).toString().compare("1")==0) // Program checking if the First value of the Trimester table is Trimester No 1
                {
                    Trimester* t = new Trimester1(); //If program finds any Trimester Year that has Trimester No 1 Then new trimester1 pointer will be created on the Program's memory
                    //From this state Program will store the data from database server and add them to there respected memory location which is based on Trimester and its courses
                    t->setTrimester(trmstr.toUtf8().constData());
                    t->setStatus(trmstrNo.value(3).toBool());

                    if(trmstrNo.value(2).toString().compare("active")==0) //checking if this Trimester is active or inactive. Point to noted if program's finds any active trimester later it will assigned that trimester to current. because our policy doesn't approve more than one trimester to be open at the same time
                    {
                        currentTrimester = trmstrNo.value(1).toString()+"-1";
                        t->setActivity(trmstrNo.value(2).toString().toUtf8().constData());
                    }
                    else
                    {
                        if(trmstrNo.value(2).toString().compare("upcoming")==0) //checking if the Trimester is upcoming. Same policy as current Trimester.
                        {
                            upcomingTrimester = trmstrNo.value(1).toString()+"-1";
                            t->setActivity(trmstrNo.value(2).toString().toUtf8().constData());
                        }
                    }
                    trimester.emplace_back(t);
                    QSqlQuery trmstrNo1("SELECT *  FROM \""+trmstr+"-1\""); //selecting the courses from database in that particular year
                    while(trmstrNo1.next())
                    {
                        if(trmstrNo1.value(9).toString().compare("UnderGraduate")==0) //checking program of that course
                        {
                            //t->setTrimester(trmstr.toUtf8().constData());

                            Course* c = new UnderGraduateCourse(); //creating new course
                            int in=0;
                            //setting up courses from server datas
                            c->setCourseCode(trmstrNo1.value(0).toString().toUtf8().constData());
                            c->setCourseName(trmstrNo1.value(1).toString().toUtf8().constData());
                            c->setCreditHours(trmstrNo1.value(2).toInt());
                            c->setPreRequisite(trmstrNo1.value(3).toString().toUtf8().constData());
                            int in1=0;
                            c->setTrimester(trimester.back());
                            c->setStatus(trmstrNo1.value(5).toBool());
                            c->setCourseVenue(trmstrNo1.value(6).toString().toUtf8().constData());
                            c->setCourseTime(trmstrNo1.value(7).toString().toUtf8().constData());
                            for(unsigned int i=0;i<faculty.size();i++)
                            {
                                if(faculty[i]->getFacultyName().compare(trmstrNo1.value(8).toString().toUtf8().constData())==0)
                                {
                                    in1++;
                                    c->setFaculty(faculty[i]);
                                    break;
                                }
                            }
                            if(in1==0)
                            {
                                c->setFaculty(nullptr);
                            }
                            for(unsigned int i=0;i<faculty.size();i++)
                            {
                                for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                {
                                    if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo1.value(4).toString().toUtf8().constData())==0)
                                    {
                                        in++;
                                        c->setAcademician(faculty[i]->getAcademician()[j]);
                                        //faculty[i]->getAcademician()[j]->addCourses(c);
                                        break;
                                    }
                                }
                            }
                            if(in==0)
                            {
                                c->setAcademician(nullptr);
                            }
                            //adding the course to the last added trimester
                            trimester.back()->addCourse(c);

                        }
                        else
                        {
                            //same as other add course to trimester process
                            if(trmstrNo1.value(9).toString().compare("PostGraduate")==0)
                            {
                                Course* c = new PostGraduateCourse();
                                c->setCourseCode(trmstrNo1.value(0).toString().toUtf8().constData());
                                c->setCourseName(trmstrNo1.value(1).toString().toUtf8().constData());
                                c->setCreditHours(trmstrNo1.value(2).toInt());
                                c->setPreRequisite(trmstrNo1.value(3).toString().toUtf8().constData());
                                c->setTrimester(trimester.back());
                                int in1=0;
                                c->setStatus(trmstrNo1.value(5).toBool());
                                c->setCourseVenue(trmstrNo1.value(6).toString().toUtf8().constData());
                                c->setCourseTime(trmstrNo1.value(7).toString().toUtf8().constData());
                                for(unsigned int i=0;i<faculty.size();i++)
                                {
                                    if(faculty[i]->getFacultyName().compare(trmstrNo1.value(8).toString().toUtf8().constData())==0)
                                    {
                                        in1++;
                                        c->setFaculty(faculty[i]);
                                        break;
                                    }
                                }
                                if(in1==0)
                                {
                                    c->setFaculty(nullptr);
                                }
                                int in=0;
                                for(unsigned int i=0;i<faculty.size();i++)
                                {
                                    for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                    {
                                        if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo1.value(4).toString().toUtf8().constData())==0)
                                        {
                                            in++;
                                            c->setAcademician(faculty[i]->getAcademician()[j]);
                                            //faculty[i]->getAcademician()[j]->addCourses(c);
                                            break;
                                        }
                                    }
                                }
                                if(in==0)
                                {
                                    c->setAcademician(nullptr);
                                }
                                trimester.back()->addCourse(c);
                            }
                            else
                            {
                                //same as other add course to trimester process
                                if(trmstrNo1.value(9).toString().compare("Diploma")==0)
                                {
                                    //Trimester* t = new Trimester1();
                                    //t->setTrimester(trmstr.toUtf8().constData());
                                    Course* c = new DiplomaCourse();
                                    c->setCourseCode(trmstrNo1.value(0).toString().toUtf8().constData());
                                    c->setCourseName(trmstrNo1.value(1).toString().toUtf8().constData());
                                    c->setCreditHours(trmstrNo1.value(2).toInt());
                                    c->setPreRequisite(trmstrNo1.value(3).toString().toUtf8().constData());
                                    c->setTrimester(trimester.back());
                                    int in1=0;
                                    c->setStatus(trmstrNo1.value(5).toBool());
                                    c->setCourseVenue(trmstrNo1.value(6).toString().toUtf8().constData());
                                    c->setCourseTime(trmstrNo1.value(7).toString().toUtf8().constData());
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        if(faculty[i]->getFacultyName().compare(trmstrNo1.value(8).toString().toUtf8().constData())==0)
                                        {
                                            in1++;
                                            c->setFaculty(faculty[i]);
                                            break;
                                        }
                                    }
                                    if(in1==0)
                                    {
                                        c->setFaculty(nullptr);
                                    }
                                    int in=0;
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                        {
                                            if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo1.value(4).toString().toUtf8().constData())==0)
                                            {
                                                in++;
                                                c->setAcademician(faculty[i]->getAcademician()[j]);
                                                //faculty[i]->getAcademician()[j]->addCourses(c);
                                                break;
                                            }
                                        }
                                    }
                                    if(in==0)
                                    {
                                        c->setAcademician(nullptr);
                                    }
                                    trimester.back()->addCourse(c);
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(trmstrNo.value(0).toString()=="2")// Program checking if the First value of the Trimester table is Trimester No 2
                    {
                        Trimester* t = new Trimester2();
                        t->setTrimester(trmstr.toUtf8().constData());
                        t->setStatus(trmstrNo.value(3).toBool());
                        if(trmstrNo.value(2).toString().compare("active")==0)
                        {
                            currentTrimester = trmstrNo.value(1).toString()+"-2";
                            t->setActivity(trmstrNo.value(2).toString().toUtf8().constData());
                        }
                        else
                        {
                            if(trmstrNo.value(2).toString().compare("upcoming")==0)
                            {
                                upcomingTrimester = trmstrNo.value(1).toString()+"-2";
                                t->setActivity(trmstrNo.value(2).toString().toUtf8().constData());
                            }
                        }
                        trimester.emplace_back(t);
                        QSqlQuery trmstrNo2("SELECT *  FROM \""+trmstr+"-2\"");
                        while(trmstrNo2.next())
                        {
                            if(trmstrNo2.value(9).toString().compare("UnderGraduate")==0)
                            {

                                //t->setTrimester(trmstr.toUtf8().constData());
                                Course* c = new UnderGraduateCourse();
                                c->setCourseCode(trmstrNo2.value(0).toString().toUtf8().constData());
                                c->setCourseName(trmstrNo2.value(1).toString().toUtf8().constData());
                                c->setCreditHours(trmstrNo2.value(2).toInt());
                                c->setPreRequisite(trmstrNo2.value(3).toString().toUtf8().constData());
                                c->setTrimester(trimester.back());
                                int in1=0;
                                c->setStatus(trmstrNo2.value(5).toBool());
                                c->setCourseVenue(trmstrNo2.value(6).toString().toUtf8().constData());
                                c->setCourseTime(trmstrNo2.value(7).toString().toUtf8().constData());
                                for(unsigned int i=0;i<faculty.size();i++)
                                {
                                    if(faculty[i]->getFacultyName().compare(trmstrNo2.value(8).toString().toUtf8().constData())==0)
                                    {
                                        in1++;
                                        c->setFaculty(faculty[i]);
                                        break;
                                    }
                                }
                                if(in1==0)
                                {
                                    c->setFaculty(nullptr);
                                }
                                int in=0;
                                for(unsigned int i=0;i<faculty.size();i++)
                                {
                                    for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                    {
                                        if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo2.value(4).toString().toUtf8().constData())==0)
                                        {
                                            in++;
                                            c->setAcademician(faculty[i]->getAcademician()[j]);
                                            //faculty[i]->getAcademician()[j]->addCourses(c);
                                            break;
                                        }
                                    }
                                }
                                if(in==0)
                                {
                                    c->setAcademician(nullptr);
                                }
                                trimester.back()->addCourse(c);
                            }
                            else
                            {
                                if(trmstrNo2.value(9).toString().compare("PostGraduate")==0)
                                {
                                    Course* c = new PostGraduateCourse();
                                    c->setCourseCode(trmstrNo2.value(0).toString().toUtf8().constData());
                                    c->setCourseName(trmstrNo2.value(1).toString().toUtf8().constData());
                                    c->setCreditHours(trmstrNo2.value(2).toInt());
                                    c->setPreRequisite(trmstrNo2.value(3).toString().toUtf8().constData());
                                    c->setTrimester(trimester.back());
                                    int in1=0;
                                    c->setStatus(trmstrNo2.value(5).toBool());
                                    c->setCourseVenue(trmstrNo2.value(6).toString().toUtf8().constData());
                                    c->setCourseTime(trmstrNo2.value(7).toString().toUtf8().constData());
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        if(faculty[i]->getFacultyName().compare(trmstrNo2.value(8).toString().toUtf8().constData())==0)
                                        {
                                            in1++;
                                            c->setFaculty(faculty[i]);
                                            break;
                                        }
                                    }
                                    if(in1==0)
                                    {
                                        c->setFaculty(nullptr);
                                    }
                                    int in=0;
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                        {
                                            if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo2.value(4).toString().toUtf8().constData())==0)
                                            {
                                                in++;
                                                c->setAcademician(faculty[i]->getAcademician()[j]);
                                                //faculty[i]->getAcademician()[j]->addCourses(c);
                                                break;
                                            }
                                        }
                                    }
                                    if(in==0)
                                    {
                                        c->setAcademician(nullptr);
                                    }
                                    trimester.back()->addCourse(c);
                                }
                                else
                                {
                                    if(trmstrNo2.value(9).toString().compare("Diploma")==0)
                                    {
                                        //Trimester* t = new Trimester1();
                                        //t->setTrimester(trmstr.toUtf8().constData());
                                        Course* c = new DiplomaCourse();
                                        c->setCourseCode(trmstrNo2.value(0).toString().toUtf8().constData());
                                        c->setCourseName(trmstrNo2.value(1).toString().toUtf8().constData());
                                        c->setCreditHours(trmstrNo2.value(2).toInt());
                                        c->setPreRequisite(trmstrNo2.value(3).toString().toUtf8().constData());
                                        c->setTrimester(trimester.back());
                                        int in1=0;
                                        c->setStatus(trmstrNo2.value(5).toBool());
                                        c->setCourseVenue(trmstrNo2.value(6).toString().toUtf8().constData());
                                        c->setCourseTime(trmstrNo2.value(7).toString().toUtf8().constData());
                                        for(unsigned int i=0;i<faculty.size();i++)
                                        {
                                            if(faculty[i]->getFacultyName().compare(trmstrNo2.value(8).toString().toUtf8().constData())==0)
                                            {
                                                in1++;
                                                c->setFaculty(faculty[i]);
                                                break;
                                            }
                                        }
                                        if(in1==0)
                                        {
                                            c->setFaculty(nullptr);
                                        }
                                        int in=0;
                                        for(unsigned int i=0;i<faculty.size();i++)
                                        {
                                            for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                            {
                                                if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo2.value(4).toString().toUtf8().constData())==0)
                                                {
                                                    in++;
                                                    c->setAcademician(faculty[i]->getAcademician()[j]);
                                                    //faculty[i]->getAcademician()[j]->addCourses(c);
                                                    break;
                                                }
                                            }
                                        }
                                        if(in==0)
                                        {
                                            c->setAcademician(nullptr);
                                        }
                                        trimester.back()->addCourse(c);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if(trmstrNo.value(0).toString()=="3")// Program checking if the First value of the Trimester table is Trimester No 3
                        {
                            Trimester* t = new Trimester3();
                            t->setTrimester(trmstr.toUtf8().constData());
                            t->setStatus(trmstrNo.value(3).toBool());
                            if(trmstrNo.value(2).toString().compare("active")==0)
                            {
                                currentTrimester = trmstrNo.value(1).toString()+"-3";
                                t->setActivity(trmstrNo.value(2).toString().toUtf8().constData());
                            }
                            else
                            {
                                if(trmstrNo.value(2).toString().compare("upcoming")==0)
                                {
                                    upcomingTrimester = trmstrNo.value(1).toString()+"-3";
                                    t->setActivity(trmstrNo.value(2).toString().toUtf8().constData());
                                }
                            }
                            trimester.emplace_back(t);
                            QSqlQuery trmstrNo3("SELECT *  FROM \""+trmstr+"-3\"");
                            while(trmstrNo3.next())
                            {
                                if(trmstrNo3.value(9).toString().compare("UnderGraduate")==0)
                                {
                                    //t->setTrimester(trmstr.toUtf8().constData());
                                    Course* c = new UnderGraduateCourse();
                                    int in=0;
                                    c->setCourseCode(trmstrNo3.value(0).toString().toUtf8().constData());
                                    c->setCourseName(trmstrNo3.value(1).toString().toUtf8().constData());
                                    c->setCreditHours(trmstrNo3.value(2).toInt());
                                    c->setPreRequisite(trmstrNo3.value(3).toString().toUtf8().constData());
                                    c->setTrimester(trimester.back());
                                    int in1=0;
                                    c->setStatus(trmstrNo3.value(5).toBool());
                                    c->setCourseVenue(trmstrNo3.value(6).toString().toUtf8().constData());
                                    c->setCourseTime(trmstrNo3.value(7).toString().toUtf8().constData());
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        if(faculty[i]->getFacultyName().compare(trmstrNo3.value(8).toString().toUtf8().constData())==0)
                                        {
                                            in1++;
                                            c->setFaculty(faculty[i]);
                                            break;
                                        }
                                    }
                                    if(in1==0)
                                    {
                                        c->setFaculty(nullptr);
                                    }

                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                        {
                                            if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo3.value(4).toString().toUtf8().constData())==0)
                                            {
                                                in++;
                                                c->setAcademician(faculty[i]->getAcademician()[j]);

                                                //faculty[i]->getAcademician()[j]->addCourses(c);
                                                break;
                                            }
                                        }
                                    }
                                    if(in==0)
                                    {
                                        c->setAcademician(nullptr);
                                    }

                                    trimester.back()->addCourse(c);

                                }
                                else
                                {
                                    if(trmstrNo3.value(9).toString().compare("PostGraduate")==0)
                                    {
                                        Course* c = new PostGraduateCourse();
                                        c->setCourseCode(trmstrNo3.value(0).toString().toUtf8().constData());
                                        c->setCourseName(trmstrNo3.value(1).toString().toUtf8().constData());
                                        c->setCreditHours(trmstrNo3.value(2).toInt());
                                        c->setPreRequisite(trmstrNo3.value(3).toString().toUtf8().constData());
                                        c->setTrimester(trimester.back());
                                        int in1=0;
                                        c->setStatus(trmstrNo3.value(5).toBool());
                                        c->setCourseVenue(trmstrNo3.value(6).toString().toUtf8().constData());
                                        c->setCourseTime(trmstrNo3.value(7).toString().toUtf8().constData());
                                        for(unsigned int i=0;i<faculty.size();i++)
                                        {
                                            if(faculty[i]->getFacultyName().compare(trmstrNo3.value(8).toString().toUtf8().constData())==0)
                                            {
                                                in1++;
                                                c->setFaculty(faculty[i]);
                                                break;
                                            }
                                        }
                                        if(in1==0)
                                        {
                                            c->setFaculty(nullptr);
                                        }
                                        int in=0;
                                        for(unsigned int i=0;i<faculty.size();i++)
                                        {
                                            for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                            {
                                                if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo3.value(4).toString().toUtf8().constData())==0)
                                                {
                                                    in++;
                                                    c->setAcademician(faculty[i]->getAcademician()[j]);
                                                    //faculty[i]->getAcademician()[j]->addCourses(c);
                                                    break;
                                                }
                                            }
                                        }
                                        if(in==0)
                                        {
                                            c->setAcademician(nullptr);
                                        }
                                        trimester.back()->addCourse(c);
                                    }
                                    else
                                    {
                                        if(trmstrNo3.value(9).toString().compare("Diploma")==0)
                                        {
                                            //Trimester* t = new Trimester1();
                                            //t->setTrimester(trmstr.toUtf8().constData());
                                            Course* c = new DiplomaCourse();
                                            c->setCourseCode(trmstrNo3.value(0).toString().toUtf8().constData());
                                            c->setCourseName(trmstrNo3.value(1).toString().toUtf8().constData());
                                            c->setCreditHours(trmstrNo3.value(2).toInt());
                                            c->setPreRequisite(trmstrNo3.value(3).toString().toUtf8().constData());
                                            c->setTrimester(trimester.back());
                                            int in1=0;
                                            c->setStatus(trmstrNo3.value(5).toBool());
                                            c->setCourseVenue(trmstrNo3.value(6).toString().toUtf8().constData());
                                            c->setCourseTime(trmstrNo3.value(7).toString().toUtf8().constData());
                                            for(unsigned int i=0;i<faculty.size();i++)
                                            {
                                                if(faculty[i]->getFacultyName().compare(trmstrNo3.value(8).toString().toUtf8().constData())==0)
                                                {
                                                    in1++;
                                                    c->setFaculty(faculty[i]);
                                                    break;
                                                }
                                            }
                                            if(in1==0)
                                            {
                                                c->setFaculty(nullptr);
                                            }
                                            int in=0;
                                            for(unsigned int i=0;i<faculty.size();i++)
                                            {
                                                for(unsigned int j=0;j<faculty[i]->getAcademician().size();j++)
                                                {
                                                    if(faculty[i]->getAcademician()[j]->getUserID().compare(trmstrNo3.value(4).toString().toUtf8().constData())==0)
                                                    {
                                                        in++;
                                                        c->setAcademician(faculty[i]->getAcademician()[j]);
                                                        //faculty[i]->getAcademician()[j]->addCourses(c);
                                                        break;
                                                    }
                                                }
                                            }
                                            if(in==0)
                                            {
                                                c->setAcademician(nullptr);
                                            }
                                            trimester.back()->addCourse(c);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //bellow this the part specially coded for adding student to courses. which of them contains in faculty and trimester respectively, this part will be make the program slow (0(n^5))
        for(unsigned int i=0;i<faculty.size();i++)
        {
            for(unsigned int j=0;j<faculty[i]->getStudent().size();j++)
            {
                //adding student list to course
                QSqlQuery qryAddStudentsToCourse("SELECT * FROM \""+QString::fromStdString(faculty[i]->getStudent()[j]->getUserID())+"\"");
                while(qryAddStudentsToCourse.next())
                {
                    for(unsigned int k=0;k<trimester.size();k++)
                    {
                        for(unsigned int l=0;l<trimester[k]->getCourse().size();l++)
                        {
                            if(trimester[k]->getTrimester()+"-"+std::to_string(trimester[k]->getTrimesterNo())==(qryAddStudentsToCourse.value(1).toString()+"-"+qryAddStudentsToCourse.value(2).toString()).toUtf8().constData())
                            {
                                if(trimester[k]->getCourse()[l]->getCourseCode()==qryAddStudentsToCourse.value(0).toString().toUtf8().constData())
                                {
                                    faculty[i]->getStudent()[j]->addCourse(trimester[k]->getCourse()[l]);
                                    trimester[k]->getCourse()[l]->addStudent(faculty[i]->getStudent()[j]);
                                }
                            }
                        }
                    }
                }
            }
        }/*
        for(unsigned int k=0;k<trimester.size();k++)
        {
            for(unsigned int l=0;l<trimester[k]->getCourse().size();l++)
            {
                for(unsigned int m=0;m<trimester[k]->getCourse()[l]->getStudent().size();m++)
                {
                    qDebug() << QString::fromStdString(trimester[k]->getTrimester()) <<"-"<< QString::number(trimester[k]->getTrimesterNo())<<" " <<QString::fromStdString(trimester[k]->getCourse()[l]->getCourseCode())<<" "<<QString::fromStdString(trimester[k]->getCourse()[l]->getStudent()[m]->getUserID());
                }
            }
        }
        */
    }
    db.close();
    return isOpen;
}
void MainMenu::on_logOutButton_clicked()
{
    databaseIsOK = getAllDataFromServer(); //program will refresh the information for next login
    emit buttonClicked(); //emitting signal to logInDialog to show it
    this->close(); //hiding main menu
}
void MainMenu::adminMenuCurrentTrimester() //Setting up the ui for admin's current Trimester form
{
    ui->trimesterComboBox->clear();
    ui->trimesterComboBoxUpcoming->clear();
    //unsigned int count=0;
    for(unsigned int i=0;i<trimester.size();i++)
    {
         ui->trimesterComboBox->addItem(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()));
         //qDebug() << QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()) <<"\n";
    }
    for(unsigned int i=0;i<trimester.size();i++)
    {
         ui->trimesterComboBoxUpcoming->addItem(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()));
    }
    //
    ui->currentTrimesterIs->setStyleSheet("QLabel { color : green; }");
    ui->currentTrimesterIs->setText("Current Trimester is: "+currentTrimester);
    ui->upcomingTrimesterLabel->setStyleSheet("QLabel { color : green; }");
    ui->upcomingTrimesterLabel->setText("Upcoming Trimester is: "+upcomingTrimester);
}
void MainMenu::adminMenuAddTrimester() //Setting up the ui for admin's Add Trimester form
{
    ui->showTrimesterError->clear();
    ui->addTrimesterLineEdit->clear();
    ui->addAvailabiltyCheckBox->setChecked(false);
}
void MainMenu::on_addTrimesterButtonOk_clicked()// storing trimester into memory and database
{
    bool ischecked=false;
    if(ui->addAvailabiltyCheckBox->isChecked()) //checking the check box is true
    {
        ischecked = true;
    }
    QString addedtrimester = ui->addTrimesterLineEdit->text()+"-"+ui->addTrimisterComboBox->currentText();
    int count=0; // to keep track how many trimester has already there similar to entered trimester
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(addedtrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0) //comparing existing trimester to entered trimester
        {
            count++;
            ui->showTrimesterError->setStyleSheet("QLabel { color : red; }");
            ui->showTrimesterError->setText(addedtrimester+" already exits"); // showing alreading if exists
            break;
        }
    }
    if(count==0)
    {
        qDebug() << ui->addTrimesterLineEdit->text().size();
        if(ui->addTrimesterLineEdit->text()[2]!='/'||ui->addTrimesterLineEdit->text().size()!=5) // making sure that entered trimester's format is yy/yy
        {
            ui->showTrimesterError->setStyleSheet("QLabel { color : red; }");
            ui->showTrimesterError->setText("Invalid Format"); //showing error
        }
        else
        {
            Trimester* t= admin->addTrimester(ui->addTrimesterLineEdit->text().toUtf8().constData(),ischecked,"null",ui->addTrimisterComboBox->currentText().toInt()); // if all okay, creating new trimester from admin which invokes the method addtrimester. sending the values gathered from add trimester form
            if(t!=nullptr) // if newly created trimester return nullptr(but shouldn't we already verified the entered data to create new trimester, just in case), it will not continue. else storing data into database
            {
                if(db.open()) //adding trimester data in database if open
                {
                    //First up is to insert new trimester into Trimester Table. if already exists/inserted just continue to next process
                    QSqlQuery query;
                    query.prepare("INSERT INTO \"Trimester\" (trimester) VALUES ('"+ui->addTrimesterLineEdit->text()+"')");
                    query.exec();

                    //Second is creating a new query to create a table for that Trimester. to keep track and select trimester year and trimester no from database during addallfromdatabase() operation. if exist skipped to the next insert query
                    QSqlQuery queryCreateThisTrimester;

                    //We've created a function in database to minimise the coding for creating trimester table every time. so this function will create the new trimester or if exist already, will just return void.
                    queryCreateThisTrimester.prepare("SELECT public.createtrimestertable('"+ui->addTrimesterLineEdit->text()+"')");
                    queryCreateThisTrimester.exec();

                    //Third is to insert the values of trimester no, year, status, and avalabilty into the newly or existing trimester table.
                    QSqlQuery queryInsertThisTrimester;
                    QString booltxt = ischecked ? "TRUE" : "FALSE";
                    queryInsertThisTrimester.prepare("INSERT INTO \""+ui->addTrimesterLineEdit->text()+"\" (\"trimesterNo\", \"trimesterYear\", status, \"isOpen\") VALUES ('"+ui->addTrimisterComboBox->currentText()+"', '"+ui->addTrimesterLineEdit->text()+"', 'null', "+booltxt+")");
                    queryInsertThisTrimester.exec();

                    //Forth is to create table in database to store courses for that particular Trimester. format should be 'yy/yy-#'
                    QSqlQuery queryCreateThisTrimesterNo;
                    queryCreateThisTrimester.prepare("SELECT public.createtrimesternotable('"+ui->addTrimesterLineEdit->text()+"-"+ui->addTrimisterComboBox->currentText()+"')");
                    queryCreateThisTrimesterNo.exec();

                    //excuting and checking if all the execution of queries return false. if false then there is something wrong in the database side.
                    if(!query.exec()&&!queryCreateThisTrimester.exec()&&!queryInsertThisTrimester.exec()&&!queryCreateThisTrimesterNo.exec())
                    {

                         QMessageBox::critical(this,"Error", "Failed to create "+QString::fromStdString(trimester.back()->getTrimester())+"-"+ui->addTrimisterComboBox->currentText()+" in database");
                         //qDebug() << queryCreateThisTrimester.lastError();
                    }
                    else
                    {
                        //If database storing is ok then the program will Add the Trimester Pointer to vecotr<Trimester*>
                        trimester.emplace_back(t);
                        ui->showTrimesterError->setStyleSheet("QLabel { color : Green; }");
                        ui->showTrimesterError->setText("Trimester Created"); //Confirming Admin that creating Trimester is successfull
                    }
                }
                else
                {
                    //Showing error if connection to database is lost.
                    QMessageBox::critical(this,"Error", "Database connection lost");
                }
                db.close();
            }
            else
            {
                delete t;
            }
        }
    }
}
void MainMenu::on_currentTrimesterSelected_clicked()
{
    //admin menu current trimester select
    std::string currentTrim = ui->trimesterComboBox->currentText().toUtf8().constData();
    //char trimNo = currentTrim[6];
    std::string upcomingTrim = ui->trimesterComboBoxUpcoming->currentText().toUtf8().constData();
    //char upTrim = upcomingTrim[6];
    std::string trimYear = currentTrim.substr(0, currentTrim.size()-2);
    std::string pastTrimester = currentTrimester.toUtf8().constData();
    //qDebug() <<trimNo<<" "<<QString::fromStdString(trimYear);
    if(db.open())
    {
        QSqlQuery exitsingTQuery; //QString::fromStdString(currentTrim)
        exitsingTQuery.prepare("UPDATE \""+QString::fromStdString(pastTrimester.substr(0, pastTrimester.size()-2))+"\" SET status='inactive', \"isOpen\"=FALSE WHERE \"trimesterNo\" = '"+pastTrimester[6]+"'");
        bool x = exitsingTQuery.exec();
        QSqlQuery setCurrentTQuery;
        setCurrentTQuery.prepare("UPDATE \""+QString::fromStdString(currentTrim.substr(0, currentTrim.size()-2))+"\" SET status='active', \"isOpen\"=TRUE "
                                                                                                                 ""
                                                                                                                 ""
                                                                                                                 " \"trimesterNo\" = '"+currentTrim[6]+"'");
        bool y = setCurrentTQuery.exec();
        QSqlQuery setUpcomingTQuery;
        setUpcomingTQuery.prepare("UPDATE \""+QString::fromStdString(upcomingTrim.substr(0, upcomingTrim.size()-2))+"\" SET status='upcoming', \"isOpen\"=FALSE WHERE \"trimesterNo\" = '"+upcomingTrim[6]+"'");
        bool z = setUpcomingTQuery.exec();
        if(!x&&!y&&!z)
        {
            QMessageBox::critical(this,"Error", "Failed to save data in database");
            QSqlQuery rollback;
            rollback.prepare("ROLLBACK");
            rollback.exec();
            rollback.prepare("ROLLBACK");
            rollback.exec();
            rollback.prepare("ROLLBACK");
            rollback.exec();
        }
        else
        {
            for(unsigned int i=0;i<trimester.size();i++)
            {
                if(QString::fromStdString(pastTrimester).compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
                {
                    trimester[i]->setStatus(false);
                    trimester[i]->setActivity("inactive");
                    break;
                }
            }

            for(unsigned int i=0;i<trimester.size();i++)
            {
                if(QString::fromStdString(currentTrim).compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
                {

                    trimester[i]->setStatus(true);
                    trimester[i]->setActivity("active");

                    currentTrimester = QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo());
                }
            }
            for(unsigned int i=0;i<trimester.size();i++)
            {
                if(QString::fromStdString(upcomingTrim).compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
                {
                    trimester[i]->setStatus(false);
                    trimester[i]->setActivity("upcoming");
                    upcomingTrimester = QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo());
                }
            }
            ui->setTrimesterInfoLabel->setStyleSheet("QLabel { color : green; }");
            ui->setTrimesterInfoLabel->setText("Current And Upcoming Trimester is set");
            ui->currentTrimesterLabel->setText("Current Trimester: "+currentTrimester+", Upcomng Trimester: "+upcomingTrimester);
        }
    }
    else
    {
        ui->setTrimesterInfoLabel->setStyleSheet("QLabel { color : red; }");
        ui->setTrimesterInfoLabel->setText("Database Connection not found");
    }
    db.close();
}
void MainMenu::setAvailabilty()
{
    //admin menu set availabilty for trimester. setting up menu
    ui->showtextSetAvailabiltyForm->setText("Warning Changing the availability might affect other users");
    ui->currentTrimesterCheckBoxLabel->setText("Current Trimester: "+currentTrimester);
    ui->upcomingTrimesterCheckBoxLabel->setText("Upcoming Trimester: "+upcomingTrimester);
    bool currentState;
    bool upcomingState;
    //finding out the current trimester status
    for(unsigned int i=0; i<trimester.size();i++)
    {
        if(currentTrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
        {
            currentState = trimester[i]->checkIsOpen();
            break;
        }
    }
    //finding out the upcoming trimester status
    for(unsigned int i=0; i<trimester.size();i++)
    {
        if(upcomingTrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
        {
            upcomingState = trimester[i]->checkIsOpen();
            break;
        }
    }
    //showing the status in checkbox
    ui->checkBoxCurrentTrimesterSet->setChecked(currentState);
    ui->checkBoxUpcomingTrimesterSet->setChecked(upcomingState);

}
void MainMenu::on_setAvailabilityOk_clicked()//operation when set availabilty button clicked
{
    if(db.open()) //checking database
    {
        bool ischeckedCurrent=false;
        bool ischeckedUp=false;
        if(ui->checkBoxCurrentTrimesterSet->isChecked()) //checking the check box is true
        {
            ischeckedCurrent = true;
        }
        if(ui->checkBoxUpcomingTrimesterSet->isChecked()) //checking the check box is true
        {
            ischeckedUp = true;
        }
        QSqlQuery setcStatusQ; //query to update the trimester's status in database
        std::string currentTrim = currentTrimester.toUtf8().constData();
        std::string upTrim = upcomingTrimester.toUtf8().constData();
        QString booltxt = ischeckedCurrent ? "TRUE" : "FALSE";
        //query to update database where the trimester table yy/yy
        setcStatusQ.prepare("UPDATE \""+QString::fromStdString(currentTrim.substr(0, currentTrim.size()-2))+"\" SET \"isOpen\"="+booltxt+" WHERE \"trimesterNo\" = '"+currentTrim[6]+"'");
        bool x = setcStatusQ.exec();
        QString booltxt1 = ischeckedUp ? "TRUE" : "FALSE";
        QSqlQuery setuStatusQ;
        setuStatusQ.prepare("UPDATE \""+QString::fromStdString(upTrim.substr(0, upTrim.size()-2))+"\" SET \"isOpen\"="+booltxt1+" WHERE \"trimesterNo\" = '"+upTrim[6]+"'");
        bool y = setuStatusQ.exec();

        if(!x&&!y) //checking the sql was successful
        {
            QMessageBox::warning(this,"Error", "Problem storing the values in database");
        }
        else
        {
            //if every sql query was successfull program will update the memory for the specific trimester
            for(unsigned int i=0; i<trimester.size();i++)
            {
                if(currentTrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
                {
                    trimester[i]->setStatus(ischeckedCurrent);
                    break;
                }
            }

            for(unsigned int i=0; i<trimester.size();i++)
            {
                if(upcomingTrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
                {
                    trimester[i]->setStatus(ischeckedUp);
                    break;
                }
            }
            ui->showtextSetAvailabiltyForm->setText("Availability Set Successfully");
        }
    }
    else
    {
        QMessageBox::warning(this,"Error", "Connection to database is lost");
    }
    db.close();
}
void MainMenu::addFacultyMenu()
{
    //setting up menu for adding faculty
    ui->facultyCreateError->setStyleSheet("QLabel { color : black; }");
    ui->facultyFullNameEdit->clear();
    ui->facultyIDEdit->clear();
    ui->facultyCreateError->clear();
}
void MainMenu::on_createFacultyButton_clicked()//Inserting create faculty data in
{
    //assigning QString to std for ease
    std::string facultyID = ui->facultyIDEdit->text().toUtf8().constData();
    std::string facultyName = ui->facultyFullNameEdit->text().toUtf8().constData();
    //some error checking
    if(facultyName.length()==0)
    {
        ui->facultyCreateError->setStyleSheet("QLabel { color : red; }");
        ui->facultyCreateError->setText("Please enter Faculty Name!");
        return;
    }
    else
    {
        if(facultyID.length()==0)
        {
            ui->facultyCreateError->setStyleSheet("QLabel { color : red; }");
            ui->facultyCreateError->setText("Please enter Faculty Initial!");
            return;
        }
        else
        {
            for(unsigned int i=0;i<faculty.size();i++)
            {
                if(faculty[i]->getFacultyFullName().compare(facultyName)==0)
                {
                    ui->facultyCreateError->setStyleSheet("QLabel { color : red; }");
                    ui->facultyCreateError->setText(QString::fromStdString(faculty[i]->getFacultyFullName())+" already Exists!");
                    return;
                }
            }
            for(unsigned int i=0;i<faculty.size();i++)
            {
                if(faculty[i]->getFacultyName().compare(facultyID)==0)
                {
                    ui->facultyCreateError->setStyleSheet("QLabel { color : red; }");
                    ui->facultyCreateError->setText(QString::fromStdString(faculty[i]->getFacultyName())+" already Exists!");
                    return;
                }
            }
            //checking database availability and adding the new faculty
            if(db.open())
            {
                QSqlQuery query;
                query.prepare("INSERT INTO \"Faculty\" (\"facultyName\", \"facultyFullName\") VALUES ('"+ui->facultyIDEdit->text()+"','"+ui->facultyFullNameEdit->text()+"')");
                bool x = query.exec();
                if(!x) //checking the excecution for insert is ok
                {
                    QMessageBox::critical(this,"Database Error","Error inserting faculty to database.");
                }
                else
                {
                    //if all went correct program will add the new faculty into memory
                    faculty.emplace_back(admin->createFaculty(facultyID, facultyName));
                    ui->facultyCreateError->setStyleSheet("QLabel { color : green; }");
                    ui->facultyCreateError->setText(ui->facultyIDEdit->text()+" successfully added!");
                }
            }
            else
            {
                QMessageBox::critical(this,"Error","Unable to create connection to database.");
            }
            db.close(); //closing database
        }
    }
}
void MainMenu::adminAddUser()
{
    //setting up the menu for adding user
    ui->addUserFacultyComboBox->clear();
    ui->addUserEnterName->clear();
    ui->addUserSetID->clear();
    ui->addUserSetPassword->clear();
    ui->male->setChecked(true);
    ui->female->setChecked(false);
    ui->addUserErrorLabel->clear();
    for(unsigned int i=0;i<faculty.size();i++) //adding list of faculty to combobox
    {
        ui->addUserFacultyComboBox->addItem(QString::fromStdString(faculty[i]->getFacultyName()));
    }
}
void MainMenu::on_createUserButton_clicked()
{
    //creating new user operation when clicked ok
    ui->addUserErrorLabel->clear();
    //some error checking before creating user
    if(ui->addUserEnterName->text().length()==0)
    {
        ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
        ui->addUserErrorLabel->setText("Enter Name!");
        return;
    }
    else
    {
        if(ui->addUserSetID->text().length()==0)
        {
            ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->addUserErrorLabel->setText("Enter ID!");
            return;
        }
        else
        {
            if(ui->addUserSetPassword->text().length()==0)
            {
                ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->addUserErrorLabel->setText("Set Password!");
                return;
            }
            else
            {
                if(ui->addUserSetPassword->text().length()==0)
                {
                    ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
                    ui->addUserErrorLabel->setText("Set Password!");
                    return;
                }
                else
                {
                    char g;
                    if(ui->male->isChecked()==true)
                    {
                        g = 'm';
                    }
                    else
                    {
                        if(ui->female->isChecked()==true)
                        {
                            g = 'f';
                        }
                        else
                        {
                            ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
                            ui->addUserErrorLabel->setText("Set Gender!");
                            return;
                        }
                    }
                    //checking academician's id from all faculty if our entered id matches to any one
                    for(unsigned int i = 0;i<faculty.size();i++)
                    {
                        for(unsigned int j = 0; j<faculty[i]->getAcademician().size();j++)
                        {
                            if(faculty[i]->getAcademician()[j]->getUserID().compare(ui->addUserSetID->text().toUtf8().constData())==0)
                            {
                                ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
                                ui->addUserErrorLabel->setText("ID already exists!");
                                return;
                            }
                        }
                    }
                    //checking Students's id from all faculty if our entered id matches to any one
                    for(unsigned int i = 0;i<faculty.size();i++)
                    {
                        for(unsigned int j = 0;j< faculty[i]->getStudent().size();j++)
                        {
                            if(faculty[i]->getStudent()[j]->getUserID().compare(ui->addUserSetID->text().toUtf8().constData())==0)
                            {
                                ui->addUserErrorLabel->setStyleSheet("QLabel { color : red; }");
                                ui->addUserErrorLabel->setText("ID already exists!");
                                return;
                            }
                        }
                    }
                    if(db.open())
                    {
                        ui->addUserErrorLabel->setText("Adding...");
                        //adding the datas to database
                        QSqlQuery queryUser;
                        queryUser.prepare("INSERT INTO \"User\" (\"userID\", \"userName\", \"userPassword\", \"userGender\", \"facultyName\", \"userType\") VALUES ('"+ui->addUserSetID->text()+"', '"+ui->addUserEnterName->text()+"', '"+ui->addUserSetPassword->text()+"', '"+g+"', '"+ui->addUserFacultyComboBox->currentText()+"', '"+ui->addUserTypeComboBox->currentText()+"')");
                        bool ok = queryUser.exec();
                        if(!ok) //checking the insertion was successful
                        {
                            QMessageBox::critical(this, "Error", "Unable to store data into database");
                            queryUser.prepare("ROLLBACK");
                            queryUser.exec();
                        }
                        else
                        {
                            // if all was ok program will search for the selected faculty.
                            unsigned int indexFaculty;
                            for(unsigned int i=0;i<faculty.size();i++)
                            {
                                if(faculty[i]->getFacultyName().compare(ui->addUserFacultyComboBox->currentText().toUtf8().constData())==0)
                                {
                                    indexFaculty = i;
                                    break;
                                }
                            }
                            //after finding faculty program will check the user type and add it memory
                            //createUser is a method where admin can create the user and return the newly created user
                            User* addedUser = admin->createUser(ui->addUserEnterName->text().toUtf8().constData(), ui->addUserSetID->text().toUtf8().constData() , ui->addUserSetPassword->text().toUtf8().constData(), ui->addUserTypeComboBox->currentText().toUtf8().constData(), g, faculty[indexFaculty]);
                            Academician* u = dynamic_cast<Academician*>(addedUser);
                            if(u!=nullptr)
                            {
                                //adding it to memory
                                faculty[indexFaculty]->addAcademician(u);
                                ui->addUserErrorLabel->setStyleSheet("QLabel { color : Green; }");
                                ui->addUserErrorLabel->setText("Academician Created and added into server!");
                                return;
                            }
                            else
                            {
                                //if the usertype is a case of a student program will have to create a table in database to list the newly created student's courses
                                Student* s = dynamic_cast<Student*>(addedUser);
                                {
                                    if(s!=nullptr)
                                    {
                                        //we already created a function to reduce complication on the code to create student table from his id
                                        QSqlQuery queryUserCreateDatabase;
                                        //program will create a course table for the student as his/her id by the SQL query below
                                        queryUserCreateDatabase.prepare("SELECT createusertable('"+ui->addUserSetID->text()+"')");
                                        QSqlQuery queryUserCreateTrimesterTakenDatabase;
                                        //program will also create a trimester taken table for the student
                                        queryUserCreateTrimesterTakenDatabase.prepare("SELECT createusertrimestertaken('"+ui->addUserSetID->text()+"trimesterTaken')");
                                        //excecuting query
                                        bool isTok = queryUserCreateTrimesterTakenDatabase.exec();
                                        bool isok = queryUserCreateDatabase.exec();
                                        if(!isok&&!isTok) //checking this is redundant as if the table is already exist sql will just skip the creation and return true. but just to keep safe
                                        {
                                            QMessageBox::critical(this, "Error", "Unable to create data into database");
                                        }
                                        else
                                        {
                                            // at this point every work for adding the user to database is done.
                                            //now adding it to the memory
                                            faculty[indexFaculty]->addStudent(s);
                                            ui->addUserErrorLabel->setStyleSheet("QLabel { color : Green; }");
                                            ui->addUserErrorLabel->setText("Student Created and added into server!");
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        QMessageBox::critical(this, "Error", "Unable to stablish connection to database");
                    }
                    db.close();
                }
            }
        }
    }

}
void MainMenu::adminEditUser()
{
    //setting up menu for editing user
    ui->editUserErrorShow->setStyleSheet("QLabel { color : black; }");
    ui->editUserNameChangedErrrorShow->setStyleSheet("QLabel { color : black; }");
    ui->editUserNameChangedErrrorShow->clear();
    ui->editUserEnterIDEditLine->clear();
    ui->editUserErrorShow->clear();
    //setting current sub widget as empty page
    ui->stackedWidgetEditUser->setCurrentWidget(ui->emptyPage);

}
void MainMenu::on_editUserComboBox_activated(const QString &arg1)
{
    //when the catagory of type combo box selected program will now check some error such as the entered id is ok or its null
    ui->editUserErrorShow->setStyleSheet("QLabel { color : black; }");
    ui->editUserErrorShow->setText("");
    if(ui->editUserEnterIDEditLine->text()=="")
    {
        ui->editUserErrorShow->setStyleSheet("QLabel { color : red; }");
        ui->editUserErrorShow->setText("Please Enter ID");
    }
    else
    {
        int count=0;
        if(admin->getUserID().compare(ui->editUserEnterIDEditLine->text().toUtf8().constData())==0)
        {
            count++;
            editableUser = admin;
        }
        else
        {
            //program will search for the entered id to check if the id is valid. if yes program will set editable user pointing to the object where id is matched
            for(unsigned int i=0;i<faculty.size();i++)
            {
                for(unsigned int j=0; j<faculty[i]->getAcademician().size();j++)
                {
                    if(faculty[i]->getAcademician()[j]->getUserID().compare(ui->editUserEnterIDEditLine->text().toUtf8().constData())==0)
                    {
                        count++;
                        editableUser = faculty[i]->getAcademician()[j];
                        break;
                    }
                }
                for(unsigned int j=0;j<faculty[i]->getStudent().size();j++)
                {
                    if(faculty[i]->getStudent()[j]->getUserID().compare(ui->editUserEnterIDEditLine->text().toUtf8().constData())==0)
                    {
                        count++;

                        editableUser = faculty[i]->getStudent()[j];
                        break;
                    }
                }
            }
        }
        //if not found program will let admin know
        if(count==0)
        {
            ui->editUserErrorShow->setText("ID Not Found");
        }
        else
        {
            //final check to ensure the catagory is selected
            if(arg1.compare("Select")==0)
            {
                ui->editUserErrorShow->setStyleSheet("QLabel { color : black; }");
                ui->editUserErrorShow->setText("");
                ui->stackedWidgetEditUser->setCurrentWidget(ui->emptyPage);
            }
            else
            {
                if(arg1.compare("Name")==0)
                {

                    ui->editUserShowCurrentName->setText("Current Name: "+QString::fromStdString(editableUser->getUserName()));
                    ui->stackedWidgetEditUser->setCurrentWidget(ui->editNamePage);
                }
                else
                {
                    if(arg1.compare("Gender")==0)
                    {
                        ui->currentGenderNameLabel->setText("Name: "+QString::fromStdString(editableUser->getUserName()));
                        if(editableUser->getUserGender()=='m')
                        {
                            ui->editUserCurrentGenderLabel->setText("Current Gender: Male");
                        }
                        else
                        {
                            if(editableUser->getUserGender()=='f')
                            {
                                ui->editUserCurrentGenderLabel->setText("Current Gender: Female");
                            }
                        }

                        ui->stackedWidgetEditUser->setCurrentWidget(ui->editGenderPage);
                    }
                    else
                    {
                        //checking faculty
                        if(arg1.compare("Faculty")==0)
                        {
                            ui->edituserFacultyComboBox->clear();
                            Admin* a = dynamic_cast<Admin*>(editableUser);
                            if(a!=nullptr)
                            {
                                ui->editUserErrorShow->setStyleSheet("QLabel { color : red; }");
                                ui->editUserErrorShow->setText("Admin has no Faculty");
                                ui->stackedWidgetEditUser->setCurrentWidget(ui->emptyPage);
                            }
                            else
                            {
                                Academician* ac = dynamic_cast<Academician*>(editableUser);
                                if(ac!=nullptr)
                                {
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        ui->edituserFacultyComboBox->addItem(QString::fromStdString(faculty[i]->getFacultyName()));
                                    }
                                    ui->editUserChangedFacultyName->setText("Name: "+QString::fromStdString(ac->getUserName()));
                                    ui->editCurrentUserFacultyLabel->setText("Current Faculty: "+QString::fromStdString(ac->getFaculty()->getFacultyName()));
                                    ui->stackedWidgetEditUser->setCurrentWidget(ui->editFacultyPage);
                                }
                                else
                                {
                                    for(unsigned int i=0;i<faculty.size();i++)
                                    {
                                        ui->edituserFacultyComboBox->addItem(QString::fromStdString(faculty[i]->getFacultyName()));
                                    }
                                    Student* s = dynamic_cast<Student*>(editableUser);
                                    if(s!=nullptr)
                                    {
                                        ui->editUserChangedFacultyName->setText("Name: "+QString::fromStdString(s->getUserName()));
                                        ui->editCurrentUserFacultyLabel->setText("Current Faculty: "+QString::fromStdString(s->getFaculty()->getFacultyName()));
                                        ui->stackedWidgetEditUser->setCurrentWidget(ui->editFacultyPage);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void MainMenu::on_editNamePageChangeName_clicked() //edit user subwidget operation for name change
{
    try
    {
        if(editableUser->getUserID().compare(ui->editUserEnterIDEditLine->text().toUtf8().constData())==0)
        {
            if(ui->enterNewNamelineEdit->text()=="") //making sure newly entered name is not null
            {
                ui->editUserNameChangedErrrorShow->setStyleSheet("QLabel { color : red; }");
                ui->editUserNameChangedErrrorShow->setText("Please Enter Name.");
            }
            else
            {
                if(db.open())
                {
                    //adding to database
                    QSqlQuery updateNameQuery;
                    updateNameQuery.prepare("UPDATE \"User\" SET \"userName\"= '"+ui->enterNewNamelineEdit->text()+"' WHERE \"userID\" = '"+QString::fromStdString(editableUser->getUserID())+"'");
                    bool ok = updateNameQuery.exec();
                    if(!ok)
                    {
                        QMessageBox::critical(this, "Database Error", "Unable to set name.");
                    }
                    else
                    {
                        editableUser->setUserName(ui->enterNewNamelineEdit->text().toUtf8().constData());
                        ui->enterNewNamelineEdit->clear();
                        ui->editUserNameChangedErrrorShow->setStyleSheet("QLabel { color : green; }");
                        ui->editUserNameChangedErrrorShow->setText("New name set to: "+QString::fromStdString(editableUser->getUserName()));
                        //ui->editUserEnterIDEditLine->setText("Current Name: "+QString::fromStdString(editableUser->getUserName()));
                    }
                }
                else
                {
                    QMessageBox::critical(this, "Database Error", "Database not found");
                }
                db.close();
            }
        }
    }

    catch (const std::exception& e)
    {
        QMessageBox::warning(this, "Pointer Error", "Unable to set name. "+QString::fromStdString(e.what()));
        ui->editUserErrorShow->setStyleSheet("QLabel { color : red; }");
        ui->editUserErrorShow->setText("Please Enter ID");
        return;
    }

}
void MainMenu::on_editGenderPageChangeGender_clicked()//edit user subwidget operation for gender change
{
    if(db.open())
    {
        QString g;
        char s;
        if(ui->userEditGenderCombox->currentText()=="Male")
        {
            g = 'm';
            s = 'm';
        }
        else
        {
            if(ui->userEditGenderCombox->currentText()=="Female")
            {
                g = 'f';
                s = 'f';
            }
        }
        QSqlQuery updateGenderQuery;
        updateGenderQuery.prepare("UPDATE \"User\" SET \"userGender\"= '"+g+"' WHERE \"userID\" = '"+QString::fromStdString(editableUser->getUserID())+"'");
        bool ok = updateGenderQuery.exec();
        if(!ok)
        {
            QMessageBox::critical(this, "Database Error", "Unable to set name.");
        }
        else
        {
            editableUser->setUserGender(s);
            if(editableUser->getUserGender()=='m')
            {
                ui->editUserCurrentGenderLabel->setText("Current Gender Changed to: Male");
            }
            else
            {
                if(editableUser->getUserGender()=='f')
                {
                    ui->editUserCurrentGenderLabel->setText("Current Gender Changed to: Female");
                }
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Database not found");
    }
    db.close();
}
void MainMenu::on_editUserFacultyButtonOK_clicked()//edit user subwidget operation for faculty change
{
    if(db.open())
    {
        int count = 0;
        unsigned int inF;
        for(unsigned int i = 0;i<faculty.size();i++)
        {
            if(ui->edituserFacultyComboBox->currentText().compare(QString::fromStdString(faculty[i]->getFacultyName()))==0)
            {
                count++;
                inF = i;
                break;
            }
        }
        if(count==0)
        {
            ui->editUserErrorShow->setText("Faculty mismatch error");
        }
        else
        {
            QSqlQuery updateFacultyQuery;
            updateFacultyQuery.prepare("UPDATE \"User\" SET \"facultyName\"= '"+ui->edituserFacultyComboBox->currentText()+"' WHERE \"userID\" = '"+QString::fromStdString(editableUser->getUserID())+"'");
            bool ok = updateFacultyQuery.exec();
            if(!ok)
            {
                QMessageBox::critical(this, "Database Error", "Unable to set faculty.");
            }
            else
            {
                Academician* a = dynamic_cast<Academician*>(editableUser);
                if(a!=nullptr)
                {
                    a->setFaculty(faculty[inF]);
                    ui->editCurrentUserFacultyLabel->setStyleSheet("QLabel { color : green; }");
                    ui->editCurrentUserFacultyLabel->setText("Faculty set to: "+QString::fromStdString(a->getFaculty()->getFacultyName()));
                }
                else
                {
                    Student* s = dynamic_cast<Student*>(editableUser);
                    if(s!=nullptr)
                    {
                        s->setFaculty(faculty[inF]);
                        ui->editCurrentUserFacultyLabel->setStyleSheet("QLabel { color : green; }");
                        ui->editCurrentUserFacultyLabel->setText("Faculty set to: "+QString::fromStdString(s->getFaculty()->getFacultyName()));
                    }
                }
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Database not found");
    }
    db.close();
}
void MainMenu::studentMenuEnroll()//student menu enrollment setting up
{
    ui->studentCurrentTrimesterCheckB->setDisabled(false);
    ui->studentupComingTrimesterCheckB->setDisabled(false);
    ui->studentEnrollInfoLabel->clear();
    ui->currentEnrollLabel->setText("Enroll to current Trimester: "+currentTrimester);
    ui->upcomingEnrollLabel->setText("Enroll to upcoming Trimester: "+upcomingTrimester);
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(currentTrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
        {
            if(!trimester[i]->checkIsOpen())
            {
                ui->studentCurrentTrimesterCheckB->setDisabled(true);
                ui->currentEnrollLabel->setText(currentTrimester+" is closed");
                break;
            }
        }
    }
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(upcomingTrimester.compare(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))==0)
        {
            if(!trimester[i]->checkIsOpen())
            {
                ui->studentupComingTrimesterCheckB->setDisabled(true);
                ui->upcomingEnrollLabel->setText(upcomingTrimester+" is closed");
                break;
            }
        }
    }
    if(student->getTakenTrimester().size()==0)
    {
        ui->studentEnrollInfoLabel->setText("You haven't Enroll to any Trimester");
    }
    else
    {
        int count=0;
        int count1=0;
        for(unsigned int i=0; i<student->getTakenTrimester().size();i++)
        {
            if(student->getTakenTrimester()[i].compare(currentTrimester.toUtf8().constData())==0)
            {
                count++;
                break;
            }
        }
        for(unsigned int i=0; i<student->getTakenTrimester().size();i++)
        {
            if(student->getTakenTrimester()[i].compare(upcomingTrimester.toUtf8().constData())==0)
            {
                count1++;
                break;
            }
        }
        if(count==0&&count1==0)
        {
            ui->studentEnrollInfoLabel->setText("You haven't Enroll to current Trimester and upcoming trimester");
        }
        else
        {
            if(count==0)
            {
                ui->studentEnrollInfoLabel->setText("You haven't enrolled to current trimester");
                ui->studentupComingTrimesterCheckB->setDisabled(true);
            }
            else
            {
                if(count1==0)
                {
                    ui->studentEnrollInfoLabel->setText("You're already enrolled to current Trimester. You haven't enrolled to upcoming trimester");
                    ui->studentCurrentTrimesterCheckB->setDisabled(true);
                }
                else
                {
                    ui->studentEnrollInfoLabel->setText("You are already enrolled");
                    ui->studentCurrentTrimesterCheckB->setDisabled(true);
                    ui->studentupComingTrimesterCheckB->setDisabled(true);
                }
            }
        }
    }
}
void MainMenu::on_enrollButton_clicked() //operation when enroll button clicked
{
    if(ui->studentCurrentTrimesterCheckB->isChecked())
    {
        if(db.open())
        {
            QSqlQuery insertTrimester;
            insertTrimester.prepare("INSERT INTO \""+QString::fromStdString(student->getUserID())+"trimesterTaken\" (trimester) VALUES ('"+currentTrimester+"')");
            bool isok = insertTrimester.exec();
            if(!isok)
            {
                QMessageBox::critical(this,"Database Error", "Failed to add trimester "+currentTrimester+" in database");
            }
            else
            {
                student->addTrimester(currentTrimester.toUtf8().constData());
            }
        }
        db.close();
    }
    if(ui->studentupComingTrimesterCheckB->isChecked())
    {
        if(db.open())
        {
            QSqlQuery insertTrimester;
            insertTrimester.prepare("INSERT INTO \""+QString::fromStdString(student->getUserID())+"trimesterTaken\" (trimester) VALUES('"+upcomingTrimester+"')");
            bool isok = insertTrimester.exec();
            if(!isok)
            {
                QMessageBox::critical(this,"Database Error", "Failed to add trimester "+upcomingTrimester+" in database");
            }
            else
            {
                student->addTrimester(upcomingTrimester.toUtf8().constData());
            }
        }
        db.close();
    }
    studentMenuEnroll();
}
void MainMenu::studentMenuViewCourse() //setting up menu for student course view menu aka default menu for students
{
    //setting up table properties
    ui->courseViewTable->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");
    ui->courseViewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->courseViewTable->verticalHeader()->setVisible(false);

    ui->showName->setText("Name: "+QString::fromStdString(student->getUserName()));
    ui->showFaculty->setText("Faculty: "+QString::fromStdString(student->getFaculty()->getFacultyFullName()));
    UnderGraduate* u = dynamic_cast<UnderGraduate*>(student);
    if(u!=nullptr)
    {
        ui->showProgram->setText("Program: UnderGraduate");
    }
    else
    {
        PostGraduate* p = dynamic_cast<PostGraduate*>(student);
        if(p!=nullptr)
        {
            ui->showProgram->setText("Program: PostGraduate");
        }
        else
        {
            Diploma* d = dynamic_cast<Diploma*>(student);
            if(d!=nullptr)
            {
                ui->showProgram->setText("Program: Diploma");
            }
        }
    }

    ui->showCurrentTrimesterForTable->clear();
    ui->shpwCoursesTrimesterCbox->clear();
    if(student->getTakenTrimester().size()==0)
    {
        ui->shpwCoursesTrimesterCbox->addItem("No trimester");
    }
    else
    {
        for(unsigned int i=0;i<student->getTakenTrimester().size();i++)
        {
            ui->shpwCoursesTrimesterCbox->addItem(QString::fromStdString(student->getTakenTrimester()[i]));
        }
    }
    for(unsigned int i=0;i<student->getTakenTrimester().size();i++)
    {
        if(QString::fromStdString(student->getTakenTrimester()[i])==currentTrimester)
        {
            ui->shpwCoursesTrimesterCbox->setCurrentText(QString::fromStdString(student->getTakenTrimester()[i]));
            break;
        }
    }
    //default course table set for current trimester
    viewStudentCourseTable(currentTrimester);
}
void MainMenu::on_shpwCoursesTrimesterCbox_activated(const QString &arg1) //show table as selected from trimester combo box
{
    viewStudentCourseTable(arg1);
}
void MainMenu::viewStudentCourseTable(const QString &arg1)// takes the argument as trimesterYear-trimesterNo and shows courses in table
{
    ui->showCurrentTrimesterForTable->setText("Subjects taken in Trimester: "+arg1);
    QStandardItemModel *model = new QStandardItemModel(0,6,this);
    //creating model for course
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Course Code")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Course Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Credit Hour")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Lecturer")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Venue")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Time")));

    QList<QStandardItem*> rowData;
    for(unsigned int i=0;i<student->returnCourse().size();i++)
    {
        if(arg1==QString::fromStdString(student->returnCourse()[i]->getTrimester()->getTrimester())+"-"+QString::number(student->returnCourse()[i]->getTrimester()->getTrimesterNo()))
        {
            //adding rows in to table
            rowData.clear();
            rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseCode()));
            rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseName()));
            rowData << new QStandardItem(QString::number(student->returnCourse()[i]->getCreditHours()));
            rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getAcademician()->getUserName()));
            rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseVenue()));
            rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseTime()));

            model->appendRow(rowData);
        }
    }
    //setting the model to our table
    ui->courseViewTable->setModel(model);
}
void MainMenu::courseRegisterMenu()
{
    ui->coursesOfferedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->coursesOfferedTable->verticalHeader()->setVisible(false);
    ui->coursesOfferedTable->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->coursesOfferedTable->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->coursesOfferedTable->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");
    ui->coursesOfferedTaken->clear();
    ui->coursesOfferedLabelFaculty->setText("Faculty: "+QString::fromStdString(student->getFaculty()->getFacultyFullName()));

    ui->courseRegisterOkButton->setDisabled(true);
    QStandardItemModel *model = new QStandardItemModel(0,6,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Course Code")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Course Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Credit Hour")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Lecturer")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Venue")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Time")));

    registrationAvailableTrimester="";
    bool currentTrimesterOpen = false;
    bool upcomingTrimesterOpen = false;
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(currentTrimester==QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))
        {
            if(trimester[i]->checkIsOpen())
            {
                currentTrimesterOpen=true;
                break;
            }
        }
    }
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(upcomingTrimester==QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))
        {
            if(trimester[i]->checkIsOpen())
            {
                upcomingTrimesterOpen=true;
                break;
            }
        }
    }
    if(currentTrimesterOpen)
    {
        registrationAvailableTrimester=currentTrimester;
        ui->coursesOfferTakenCourselabel->setText("Courses Taken in "+registrationAvailableTrimester);
        ui->coursesOfferedTrimesterLabel->setText("Courses Offered in Trimester: "+registrationAvailableTrimester);
    }
    else
    {
        if(upcomingTrimesterOpen)
        {
            registrationAvailableTrimester=upcomingTrimester;
            ui->coursesOfferTakenCourselabel->setText("Courses Taken in "+registrationAvailableTrimester);
            ui->coursesOfferedTrimesterLabel->setText("Courses Offered in Trimester: "+registrationAvailableTrimester);
        }
    }
    if(currentTrimesterOpen||upcomingTrimesterOpen)
    {
        bool enrolltocurrentTrim = false;
        for(unsigned int i=0;i<student->getTakenTrimester().size();i++)
        {
            if(registrationAvailableTrimester==QString::fromStdString(student->getTakenTrimester()[i]))
            {
                enrolltocurrentTrim = true;
                break;
            }
        }
        if(enrolltocurrentTrim==true)
        {
            QList<QStandardItem*> rowData;
            unsigned int indexTrimester;
            for(unsigned int i=0;i<trimester.size();i++)
            {
                if((QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo())==registrationAvailableTrimester))
                {
                    ui->courseRegisterOkButton->setDisabled(false);
                    indexTrimester = i;
                    break;
                }
            }
            //unsigned int indexCourse;
            if(trimester[indexTrimester]->checkIsOpen())
            {
                for(unsigned int i = 0;i<trimester[indexTrimester]->getCourse().size();i++)
                {
                    if(trimester[indexTrimester]->getCourse()[i]->getFaculty()==student->getFaculty())
                    {
                        UnderGraduate* studentIsUG = dynamic_cast<UnderGraduate*>(student);
                        if(studentIsUG!=nullptr)
                        {
                            UnderGraduateCourse* ugc = dynamic_cast<UnderGraduateCourse*>(trimester[indexTrimester]->getCourse()[i]);
                            if(ugc!=nullptr)
                            {
                                rowData.clear();
                                rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseCode()));
                                rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseName()));
                                rowData << new QStandardItem(QString::number(trimester[indexTrimester]->getCourse()[i]->getCreditHours()));
                                rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getAcademician()->getUserName()));
                                rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseVenue()));
                                rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseTime()));
                                model->appendRow(rowData);
                            }
                        }
                        else
                        {
                            PostGraduate* studentIsPG = dynamic_cast<PostGraduate*>(student);
                            if(studentIsPG!=nullptr)
                            {
                                PostGraduateCourse* pgc = dynamic_cast<PostGraduateCourse*>(trimester[indexTrimester]->getCourse()[i]);
                                if(pgc!=nullptr)
                                {
                                    rowData.clear();
                                    rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseCode()));
                                    rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseName()));
                                    rowData << new QStandardItem(QString::number(trimester[indexTrimester]->getCourse()[i]->getCreditHours()));
                                    rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getAcademician()->getUserName()));
                                    rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseVenue()));
                                    rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseTime()));
                                    model->appendRow(rowData);
                                }
                            }
                            else
                            {
                                Diploma* studentIsD = dynamic_cast<Diploma*>(student);
                                if(studentIsD!=nullptr)
                                {
                                    DiplomaCourse* dc = dynamic_cast<DiplomaCourse*>(trimester[indexTrimester]->getCourse()[i]);
                                    if(dc!=nullptr)
                                    {
                                        rowData.clear();
                                        rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseCode()));
                                        rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseName()));
                                        rowData << new QStandardItem(QString::number(trimester[indexTrimester]->getCourse()[i]->getCreditHours()));
                                        rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getAcademician()->getUserName()));
                                        rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseVenue()));
                                        rowData << new QStandardItem(QString::fromStdString(trimester[indexTrimester]->getCourse()[i]->getCourseTime()));
                                        model->appendRow(rowData);
                                    }
                                }
                            }
                        }
                    }
                }
                ui->coursesOfferedTable->setModel(model);
                ui->coursesOfferedTable->selectRow(0);
            }
            else
            {
                ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->coursesOfferedErrorLabel->setText(registrationAvailableTrimester+" is closed. You're not allowed to register");
            }
        }
        else
        {
            ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->coursesOfferedErrorLabel->setText("You are not enrolled in "+registrationAvailableTrimester);
            ui->courseRegisterOkButton->setDisabled(true);
        }
        for(unsigned i=0;i<student->returnCourse().size();i++)
        {
            if((QString::fromStdString(student->returnCourse()[i]->getTrimester()->getTrimester())+"-"+QString::number(student->returnCourse()[i]->getTrimester()->getTrimesterNo()))==registrationAvailableTrimester)
            {
                ui->coursesOfferedTaken->addItem(QString::fromStdString(student->returnCourse()[i]->getCourseCode()));
            }
        }
    }
    else
    {
        ui->coursesOfferTakenCourselabel->setText("Courses Unavailable");
        ui->coursesOfferedTrimesterLabel->setText("Courses Unavailable");
        ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
        ui->coursesOfferedErrorLabel->setText("Both "+currentTrimester+"(current) and "+upcomingTrimester+"(upcoming) is closed. You're not allowed to register at the moment.");
    }

}
void MainMenu::on_courseRegisterOkButton_clicked()
{
    //getting selected course code from table
    std::string getCourseName = ui->coursesOfferedTable->model()->data(ui->coursesOfferedTable->model()->index(ui->coursesOfferedTable->currentIndex().row(),0)).toString().toUtf8().constData();
    unsigned int x, y;
    bool found = false;
    for(unsigned int i =0;i<trimester.size();i++)
    {
        if(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo())==registrationAvailableTrimester)
        {
            x=i;
            break;
        }
    }
    for(unsigned int j=0;j<trimester[x]->getCourse().size();j++)
    {
        if(getCourseName.compare(trimester[x]->getCourse()[j]->getCourseCode())==0)
        {
            y=j;
            found=true;
            break;
        }
    }
    if(found)
    {
        UnderGraduate* ug = dynamic_cast<UnderGraduate*>(student);
        if(ug!=nullptr)
        {
            int returnValue = ug->registerCourse(trimester[x]->getCourse()[y]);
            if(returnValue==0)
            {
                trimester[x]->getCourse()[y]->addStudent(ug);
                ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : green; }");
                ui->coursesOfferedErrorLabel->setText(QString::fromStdString(trimester[x]->getCourse()[y]->getCourseCode())+" added!");

                if(db.open())
                {
                    QSqlQuery insertCourse;
                    insertCourse.prepare("INSERT INTO \""+QString::fromStdString(ug->getUserID())+"\"(\"courseCode\", \"courseOfferedYear\", \"courseOfferedTrimester\") VALUES ('"+QString::fromStdString(trimester[x]->getCourse()[y]->getCourseCode())+"','"+QString::fromStdString(trimester[x]->getCourse()[y]->getTrimester()->getTrimester())+"', '"+QString::number(trimester[x]->getCourse()[y]->getTrimester()->getTrimesterNo())+"')");
                    bool isok = insertCourse.exec();
                    if(!isok)
                    {
                        QMessageBox::warning(this,"Database error","Something went wrong while inserting");
                        trimester[x]->getCourse().pop_back();
                    }
                }
                else
                {
                    trimester[x]->getCourse().pop_back();
                }
                db.close();
            }
            else
            {
                if(returnValue==1)
                {
                    ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                    ui->coursesOfferedErrorLabel->setText("Course already taken");
                }
                else
                {
                    if(returnValue==2)
                    {
                        ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                        ui->coursesOfferedErrorLabel->setText("Pre Requisite not completed");
                    }
                    else
                    {
                        if(returnValue==3)
                        {
                            ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                            ui->coursesOfferedErrorLabel->setText("Maximum credit exceeds");
                        }
                        else
                        {
                            if(returnValue==4)
                            {
                                ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                                ui->coursesOfferedErrorLabel->setText("Course is closed");
                            }
                        }
                    }
                }
            }
            //qDebug() <<
        }
        else
        {
            PostGraduate* pg = dynamic_cast<PostGraduate*>(student);
            if(pg!=nullptr)
            {
                int returnValue = pg->registerCourse(trimester[x]->getCourse()[y]);
                if(returnValue==0)
                {
                    trimester[x]->getCourse()[y]->addStudent(pg);
                    ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : green; }");
                    ui->coursesOfferedErrorLabel->setText(QString::fromStdString(trimester[x]->getCourse()[y]->getCourseCode())+" added!");

                    if(db.open())
                    {
                        QSqlQuery insertCourse;
                        insertCourse.prepare("INSERT INTO \""+QString::fromStdString(ug->getUserID())+"\"(\"courseCode\", \"courseOfferedYear\", \"courseOfferedTrimester\") VALUES ('"+QString::fromStdString(trimester[x]->getCourse()[y]->getCourseCode())+"','"+QString::fromStdString(trimester[x]->getCourse()[y]->getTrimester()->getTrimester())+"', '"+QString::number(trimester[x]->getCourse()[y]->getTrimester()->getTrimesterNo())+"')");
                        bool isok = insertCourse.exec();
                        if(!isok)
                        {
                            QMessageBox::warning(this,"Database error","Something went wrong while inserting");
                            trimester[x]->getCourse().pop_back();
                        }
                    }
                    else
                    {
                        trimester[x]->getCourse().pop_back();
                    }
                }
                else
                {
                    if(returnValue==1)
                    {
                        ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                        ui->coursesOfferedErrorLabel->setText("Course already taken");
                    }
                    else
                    {
                        if(returnValue==2)
                        {
                            ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                            ui->coursesOfferedErrorLabel->setText("Pre Requisite not completed");
                        }
                        else
                        {
                            if(returnValue==3)
                            {
                                ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                                ui->coursesOfferedErrorLabel->setText("Maximum credit exceeds");
                            }
                            else
                            {
                                if(returnValue==4)
                                {
                                    ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                                    ui->coursesOfferedErrorLabel->setText("Course is closed");
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                Diploma* d = dynamic_cast<Diploma*>(student);
                if(d!=nullptr)
                {
                    int returnValue = d->registerCourse(trimester[x]->getCourse()[y]);
                    if(returnValue==0)
                    {
                        trimester[x]->getCourse()[y]->addStudent(d);
                        ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : green; }");
                        ui->coursesOfferedErrorLabel->setText(QString::fromStdString(trimester[x]->getCourse()[y]->getCourseCode())+" added!");

                        if(db.open())
                        {
                            QSqlQuery insertCourse;
                            insertCourse.prepare("INSERT INTO \""+QString::fromStdString(ug->getUserID())+"\"(\"courseCode\", \"courseOfferedYear\", \"courseOfferedTrimester\") VALUES ('"+QString::fromStdString(trimester[x]->getCourse()[y]->getCourseCode())+"','"+QString::fromStdString(trimester[x]->getCourse()[y]->getTrimester()->getTrimester())+"', '"+QString::number(trimester[x]->getCourse()[y]->getTrimester()->getTrimesterNo())+"')");
                            bool isok = insertCourse.exec();
                            if(!isok)
                            {
                                QMessageBox::warning(this,"Database error","Something went wrong while inserting");
                                trimester[x]->getCourse().pop_back();
                            }
                        }
                        else
                        {
                            trimester[x]->getCourse().pop_back();
                        }
                    }
                    else
                    {
                        if(returnValue==1)
                        {
                            ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                            ui->coursesOfferedErrorLabel->setText("Course already taken");
                        }
                        else
                        {
                            if(returnValue==2)
                            {
                                ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                                ui->coursesOfferedErrorLabel->setText("Pre Requisite not completed");
                            }
                            else
                            {
                                if(returnValue==3)
                                {
                                    ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                                    ui->coursesOfferedErrorLabel->setText("Maximum credit exceeds");
                                }
                                else
                                {
                                    if(returnValue==4)
                                    {
                                        ui->coursesOfferedErrorLabel->setStyleSheet("QLabel { color : red; }");
                                        ui->coursesOfferedErrorLabel->setText("Course is closed");
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }
    }
    courseRegisterMenu();
}
void MainMenu::courseDeleteMenu()
{
    ui->dropCourseTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dropCourseTableView->verticalHeader()->setVisible(false);
    ui->dropCourseTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->dropCourseTableView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->dropCourseTableView->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");
    ui->dropCourseDelete->setDisabled(true);
    ui->dropCourseCurrentTrimesterLabel->setText("Showing Courses From "+currentTrimester);
    //ui->dropCourseErrorLabel->clear();
    QStandardItemModel *model = new QStandardItemModel(0,6,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Course Code")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Course Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Credit Hour")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Lecturer")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Venue")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Time")));

    QString registrationAvailableTrimester;
    bool currentTrimesterOpen = false;
    bool upcomingTrimesterOpen = false;
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(currentTrimester==QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))
        {
            if(trimester[i]->checkIsOpen())
            {
                currentTrimesterOpen=true;
                break;
            }
        }
    }
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(upcomingTrimester==QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))
        {
            if(trimester[i]->checkIsOpen())
            {
                upcomingTrimesterOpen=true;
                break;
            }
        }
    }
    if(currentTrimesterOpen)
    {
        registrationAvailableTrimester=currentTrimester;
        ui->coursesOfferTakenCourselabel->setText("Courses Taken in "+registrationAvailableTrimester);
        ui->coursesOfferedTrimesterLabel->setText("Courses Offered in Trimester: "+registrationAvailableTrimester);
    }
    else
    {
        if(upcomingTrimesterOpen)
        {
            registrationAvailableTrimester=upcomingTrimester;
            ui->coursesOfferTakenCourselabel->setText("Courses Taken in "+registrationAvailableTrimester);
            ui->coursesOfferedTrimesterLabel->setText("Courses Offered in Trimester: "+registrationAvailableTrimester);
        }
    }
    if(currentTrimesterOpen||upcomingTrimesterOpen)
    {
        bool enrolltocurrentTrim = false;
        for(unsigned int i=0;i<student->getTakenTrimester().size();i++)
        {
            if(currentTrimester==QString::fromStdString(student->getTakenTrimester()[i]))
            {
                enrolltocurrentTrim = true;
                break;
            }
        }
        if(enrolltocurrentTrim==true)
        {
            QList<QStandardItem*> rowData;
            unsigned int indexTrimester;
            for(unsigned int i=0;i<trimester.size();i++)
            {
                if((QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo())==registrationAvailableTrimester))
                {
                    ui->dropCourseDelete->setDisabled(false);
                    indexTrimester = i;
                    break;
                }
            }
            //unsigned int indexCourse;
            if(trimester[indexTrimester]->checkIsOpen())
            {
                for(unsigned int i=0;i<student->returnCourse().size();i++)
                {
                    if(registrationAvailableTrimester==QString::fromStdString(student->returnCourse()[i]->getTrimester()->getTrimester())+"-"+QString::number(student->returnCourse()[i]->getTrimester()->getTrimesterNo()))
                    {
                        rowData.clear();
                        rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseCode()));
                        rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseName()));
                        rowData << new QStandardItem(QString::number(student->returnCourse()[i]->getCreditHours()));
                        rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getAcademician()->getUserName()));
                        rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseVenue()));
                        rowData << new QStandardItem(QString::fromStdString(student->returnCourse()[i]->getCourseTime()));
                        model->appendRow(rowData);
                    }
                }
                ui->dropCourseTableView->setModel(model);
            }
            else
            {
                ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->dropCourseErrorLabel->setText(registrationAvailableTrimester+" is closed. You're not allowed to drop course");
            }
        }
        else
        {
            ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->dropCourseErrorLabel->setText("You are not enrolled in "+registrationAvailableTrimester);
            ui->dropCourseDelete->setDisabled(true);
        }
    }
    else
    {
        ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
        ui->dropCourseErrorLabel->setText("Both "+currentTrimester+"(current) and "+upcomingTrimester+"(upcoming) is closed. You're not allowed to register at the moment.");
    }
}
void MainMenu::on_dropCourseDelete_clicked()
{
    std::string getCourseName = ui->dropCourseTableView->model()->data(ui->dropCourseTableView->model()->index(ui->dropCourseTableView->currentIndex().row(),0)).toString().toUtf8().constData();
    unsigned int x;
    bool found = false;
    for(unsigned int i =0;i<student->returnCourse().size();i++)
    {
        if(getCourseName.compare(student->returnCourse()[i]->getCourseCode())==0)
        {
            x=i;
            found=true;
            break;
        }
    }
    //qDebug() << "check";
    if(found)
    {
        if(student->returnCourse()[x]->checkIsOpen())
        {
            qDebug() <<student->returnCourse()[x]->getStudent().size();

            QString deletedCourseCode = QString::fromStdString(student->returnCourse()[x]->getCourseCode());
            bool isOk = student->dropCourse(student->returnCourse()[x]);

            if(isOk)
            {
                if(db.open())
                {
                    QSqlQuery deleteFromDatabase;
                    deleteFromDatabase.prepare("DELETE FROM \""+QString::fromStdString(student->getUserID())+"\" WHERE \"courseCode\" = '"+deletedCourseCode+"'");
                    bool execSucc = deleteFromDatabase.exec();
                    if(execSucc)
                    {
                        ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : green; }");
                        ui->dropCourseErrorLabel->setText("Course dropped");
                        courseDeleteMenu();
                    }
                    else
                    {
                        //qDebug() << execSucc;
                    }
                }
                else
                {
                    QMessageBox::warning(this, "Database Error", "Couldn't established database connection");
                }
                db.close();
            }
            else
            {
                ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->dropCourseErrorLabel->setText("drop unavailable");
            }
        }
        else
        {
            ui->dropCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->dropCourseErrorLabel->setText("Course is closed");
        }
    }
    else
    {

    }
}
void MainMenu::acadViewCourseMenu()
{
    ui->acadViewCourseTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->acadViewCourseTableView->verticalHeader()->setVisible(false);
    ui->acadViewCourseTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->acadViewCourseTableView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->acadViewCourseTableView->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");
    ui->acadCoursesLabel->clear();
    ui->acadViewCurrentTrimesterCourse->setText("Courses taken in trimester: "+currentTrimester);
    ui->acadViewCourseFaculty->setText("Faculty: "+QString::fromStdString(academician->getFaculty()->getFacultyFullName()));
    ui->acadSelectTrimesterComboBox->clear();
    if(trimester.size()==0)
    {
        ui->acadSelectTrimesterComboBox->addItem("No trimester");
    }
    else
    {
        for(unsigned int i=0;i<trimester.size();i++)
        {
            ui->acadSelectTrimesterComboBox->addItem(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()));
        }
    }
    ui->acadSelectTrimesterComboBox->setCurrentText(currentTrimester);
    ui->acadViewCourseTableView->setModel(acadViewCourseTable(currentTrimester));
}
QStandardItemModel* MainMenu::acadViewCourseTable(const QString& arg)
{
    //creating table model for view course
    ui->acadCoursesLabel->clear();

    QStandardItemModel *model = new QStandardItemModel(0,8,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Course Code")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Course Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Credit Hour")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Pre-requisite")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Status")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Venue")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Time")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Program")));

    unsigned int trimesterIndex;
    int count=0;
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(arg==QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()))
        {
            count++;
            trimesterIndex=i;
            break;
        }
    }
    if(count>0)
    {
        QList<QStandardItem*> rowData;
        int countCourses = 0;
        for(unsigned int i=0;i<trimester[trimesterIndex]->getCourse().size();i++)
        {
            if(trimester[trimesterIndex]->getCourse()[i]->getAcademician()->getUserID()==academician->getUserID())
            {
                countCourses++;
                rowData.clear();
                rowData << new QStandardItem(QString::fromStdString(trimester[trimesterIndex]->getCourse()[i]->getCourseCode()));
                rowData << new QStandardItem(QString::fromStdString(trimester[trimesterIndex]->getCourse()[i]->getCourseName()));
                rowData << new QStandardItem(QString::number(trimester[trimesterIndex]->getCourse()[i]->getCreditHours()));
                rowData << new QStandardItem(QString::fromStdString(trimester[trimesterIndex]->getCourse()[i]->getPreRequisite()));
                QString isOpen = "";
                if(trimester[trimesterIndex]->getCourse()[i]->checkIsOpen())
                {
                    isOpen = "Open";
                }
                else
                {
                    isOpen = "Closed";
                }
                rowData << new QStandardItem(isOpen);
                rowData << new QStandardItem(QString::fromStdString(trimester[trimesterIndex]->getCourse()[i]->getCourseVenue()));
                rowData << new QStandardItem(QString::fromStdString(trimester[trimesterIndex]->getCourse()[i]->getCourseTime()));
                UnderGraduateCourse* ugc = dynamic_cast<UnderGraduateCourse*>(trimester[trimesterIndex]->getCourse()[i]);
                if(ugc!=nullptr)
                {
                    rowData << new QStandardItem(QString::fromStdString(ugc->getProgramName()));
                }
                else
                {
                    PostGraduateCourse* pgc = dynamic_cast<PostGraduateCourse*>(trimester[trimesterIndex]->getCourse()[i]);
                    if(pgc!=nullptr)
                    {
                        rowData << new QStandardItem(QString::fromStdString(pgc->getProgramName()));
                    }
                    else
                    {
                        DiplomaCourse* dc = dynamic_cast<DiplomaCourse*>(trimester[trimesterIndex]->getCourse()[i]);
                        if(dc!=nullptr)
                        {
                            rowData << new QStandardItem(QString::fromStdString(dc->getProgramName()));
                        }
                    }
                }
                model->appendRow(rowData);
            }
        }
        //return model;
        if(countCourses==0)
        {
            ui->acadCoursesLabel->setStyleSheet("QLabel { color : red; }");
            ui->acadCoursesLabel->setText("You are not teaching any Courses in this trimester");
        }
    }
    else
    {
        ui->acadCoursesLabel->setStyleSheet("QLabel { color : red; }");
        ui->acadCoursesLabel->setText("Trimester has not found. Contact administration");
    }
    return model;
}
void MainMenu::on_acadSelectTrimesterComboBox_activated(const QString &arg1)
{
    ui->acadViewCurrentTrimesterCourse->setText("Courses taken in trimester: "+arg1);
    ui->acadViewCourseTableView->setModel(acadViewCourseTable(arg1));
    //acadViewCourseTable(arg1);
}
void MainMenu::acadAddCourse()
{
    ui->addAcadCourseFacultyLabel->setText("Faculty: "+QString::fromStdString(academician->getFaculty()->getFacultyFullName()));
    ui->addCourseTrimesterComboBox->clear();
    ui->addCourseTrimesterComboBox->addItem("Select");
    ui->addCourseTrimesterComboBox->addItem(currentTrimester);
    ui->addCourseTrimesterComboBox->addItem(upcomingTrimester);

    ui->addCourseCodeEdit->clear();
    ui->addCourseNameEdit->clear();
    ui->addCourseCreditEdit->clear();
    ui->addCoursePreRequisiteEdit->clear();
    ui->addCourseVenueEdit->clear();
    ui->addCourseTimeEdit->clear();

}
void MainMenu::on_acadAddCourseAddButton_clicked()
{
    std::string courseCode = ui->addCourseCodeEdit->text().toUtf8().constData();
    std::string courseName = ui->addCourseNameEdit->text().toUtf8().constData();
    bool isInt;
    int courseCredit = ui->addCourseCreditEdit->text().toInt(&isInt, 10);
    std::string coursePreReq = ui->addCoursePreRequisiteEdit->text().toUtf8().constData();
    std::string courseVenue = ui->addCourseVenueEdit->text().toUtf8().constData();
    std::string courseTime = ui->addCourseTimeEdit->text().toUtf8().constData();
    std::string courseFaculty = academician->getFaculty()->getFacultyName();
    std::string courseProgram = ui->addCourseProgramComboBox->currentText().toUtf8().constData();
    std::string courseTrimester = ui->addCourseTrimesterComboBox->currentText().toUtf8().constData();

    bool allok = false;
    if(courseCode.empty())
    {
        ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
        ui->addAcadCourseErrorLabel->setText("Please Type Course Code");
    }
    else
    {
        if(courseName.empty())
        {
            ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->addAcadCourseErrorLabel->setText("Please Type Course Name");
        }
        else
        {
            if(ui->addCourseCreditEdit->text().isEmpty())
            {
                ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->addAcadCourseErrorLabel->setText("Please Type Course Name");
            }
            else
            {
                if(courseCredit==0||courseCredit>=8)
                {
                    ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                    ui->addAcadCourseErrorLabel->setText("Please Enter Course Credit Between (1-9)");
                }
                else
                {
                    if(courseVenue.empty())
                    {
                        ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                        ui->addAcadCourseErrorLabel->setText("Please Enter Course's Venue Name");
                    }
                    else
                    {
                        if(courseTime.empty())
                        {
                            ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                            ui->addAcadCourseErrorLabel->setText("Please Enter Course's Time");
                        }
                        else
                        {
                            if(courseTrimester=="Select")
                            {
                                ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                                ui->addAcadCourseErrorLabel->setText("Please Choose Trimester");
                            }
                            else
                            {
                                allok=true;
                            }
                        }
                    }
                }
            }
        }
    }
    if(allok)
    {
        ui->addAcadCourseErrorLabel->clear();
        unsigned int trimesterIndex;
        for(unsigned int i=0;i<trimester.size();i++)
        {
            if(courseTrimester==trimester[i]->getTrimester()+"-"+std::to_string(trimester[i]->getTrimesterNo()))
            {
                trimesterIndex = i;
                break;
            }
        }
        int count=0;
        for(unsigned int i=0;i<trimester[trimesterIndex]->getCourse().size();i++)
        {
            if(trimester[trimesterIndex]->getCourse()[i]->getCourseCode()==courseCode)
            {
                count++;
                break;
            }
        }
        if(count>0)
        {
            ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->addAcadCourseErrorLabel->setText("Course already exists in trimester "+QString::fromStdString(courseTrimester));
        }
        else
        {
            //checking how many courses currentloggedin academician is teaching in selected trimester
            int countAcademcicanCourseTeachingForThatTrimester=0;
            for(unsigned int i=0;i<trimester[trimesterIndex]->getCourse().size();i++)
            {
                if(academician->getUserID()==trimester[trimesterIndex]->getCourse()[i]->getAcademician()->getUserID())
                {
                    countAcademcicanCourseTeachingForThatTrimester++;
                }
            }
            qDebug() << countAcademcicanCourseTeachingForThatTrimester;
            //if he/she teaches less than 3 courses program will add his new course else show the error
            if(countAcademcicanCourseTeachingForThatTrimester<=3) //here is the condition
            {
                if(db.open())
                {
                    QSqlQuery insertCourse;
                    bool isCourseChecked = ui->addCourseAvailabilityCheck->isChecked();
                    QString booltxt = isCourseChecked ? "TRUE" : "FALSE";
                    if(coursePreReq.empty())
                    {
                        insertCourse.prepare("INSERT INTO \""+QString::fromStdString(courseTrimester)+"\" (\"courseCode\", \"courseName\", \"creditHour\", \"academicianInCharge\", \"isOpen\", \"courseVenue\", \"courseTime\", \"courseFaculty\", \"courseProgram\",\"courseOfferedYear\", \"courseOfferedTrimester\") VALUES ('"+QString::fromStdString(courseCode)+"', '"+QString::fromStdString(courseName)+"', "+QString::number(courseCredit)+", '"+QString::fromStdString(academician->getUserID())+"', "+booltxt+", '"+QString::fromStdString(courseVenue)+"', '"+QString::fromStdString(courseTime)+"', '"+QString::fromStdString(courseFaculty)+"', '"+ui->addCourseProgramComboBox->currentText()+"', '"+QString::fromStdString(trimester[trimesterIndex]->getTrimester())+"', '"+QString::number(trimester[trimesterIndex]->getTrimesterNo())+"')");
                    }
                    else
                    {
                        insertCourse.prepare("INSERT INTO \""+QString::fromStdString(courseTrimester)+"\" (\"courseCode\", \"courseName\", \"creditHour\", \"preRequisite\", \"academicianInCharge\", \"isOpen\", \"courseVenue\", \"courseTime\", \"courseFaculty\", \"courseProgram\",\"courseOfferedYear\", \"courseOfferedTrimester\") VALUES ('"+QString::fromStdString(courseCode)+"', '"+QString::fromStdString(courseName)+"', "+QString::number(courseCredit)+", '"+QString::fromStdString(coursePreReq)+"', '"+QString::fromStdString(academician->getUserID())+"', "+booltxt+", '"+QString::fromStdString(courseVenue)+"', '"+QString::fromStdString(courseTime)+"', '"+QString::fromStdString(courseFaculty)+"', '"+ui->addCourseProgramComboBox->currentText()+"', '"+QString::fromStdString(trimester[trimesterIndex]->getTrimester())+"', '"+QString::number(trimester[trimesterIndex]->getTrimesterNo())+"')");
                    }
                    bool insertOk = insertCourse.exec();
                    if(insertOk)
                    {
                        academician->createCourse(courseCode, courseName, courseCredit, coursePreReq, isCourseChecked, courseVenue, courseTime, courseProgram, trimester[trimesterIndex]);
                        ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : green; }");
                        ui->addAcadCourseErrorLabel->setText("Course Added");
                    }
                    else
                    {
                        QMessageBox::critical(this,"Database error","Failed to insert into database");
                    }
                }
                else
                {
                    QMessageBox::critical(this,"Database error","Failed to connect to database");
                }
                db.close();
            }
            else
            {
                //program will let academcian know if he has/she has already taken 3 courses
                ui->addAcadCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->addAcadCourseErrorLabel->setText("Maximum 3 courses allowed to teach per trimester");
            }
        }
    }
}
void MainMenu::acadEditCourse()
{
    ui->acadEditCourseTableView->verticalHeader()->setVisible(false);
    ui->acadEditCourseTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->acadEditCourseTableView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->acadEditCourseTableView->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");

    ui->acadEditCourseFaculty->setText("Faculty: "+QString::fromStdString(academician->getFaculty()->getFacultyFullName()));

    ui->acadEditSelectTrimesterComboBox->clear();
    ui->acadEditSelectTrimesterComboBox->addItem(currentTrimester);
    ui->acadEditSelectTrimesterComboBox->addItem(upcomingTrimester);
    ui->acadEditSelectTrimesterComboBox->setCurrentText(currentTrimester);
    acadademecianEditCourseChosenTrimester=currentTrimester.toUtf8().constData();
    DelegateComboBox* courseStatusComboBox = new DelegateComboBox(this); //combobox delegate for creating a combobox in status column
    ui->acadEditCourseTableView->setModel(acadViewCourseTable(currentTrimester));
    ui->acadEditCourseTableView->setItemDelegateForColumn(4, courseStatusComboBox);
    ui->acadEditCourseTableView->setItemDelegateForColumn(7, new NotEditableDelegate(this));
    //disabling course code column. we shouldn't edit a course code as it is our main identifier
    ui->acadEditCourseTableView->setItemDelegateForColumn(0, new NotEditableDelegate(this));
}
void MainMenu::on_acadEditSelectTrimesterComboBox_activated(const QString &arg1)
{
    acadademecianEditCourseChosenTrimester=arg1.toUtf8().constData();
    ui->acadEditCourseTableView->setModel(acadViewCourseTable(arg1));
}
void MainMenu::on_acadEditCourseButton_clicked()
{
    QString getCourseCode = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),0)).toString();
    std::string getCourseName = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),1)).toString().toUtf8().constData();
    //std::string getCourseCredit = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),2)).toString().toUtf8().constData();
    bool isInt;
    int courseCredit = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),2)).toString().toInt(&isInt, 10);
    std::string getCoursePreRequisite = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),3)).toString().toUtf8().constData();
    std::string getCourseStatus = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),4)).toString().toUtf8().constData();
    std::string getCourseVenue = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),5)).toString().toUtf8().constData();
    std::string getCourseTime = ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),6)).toString().toUtf8().constData();

    bool status;
    if(getCourseStatus=="Open")
    {
        status =true;
    }
    else
    {
        if(getCourseStatus=="Close")
        {
            status = false;
        }
    }
    unsigned int choosenTrimesterIndex;
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(trimester[i]->getTrimester()+"-"+std::to_string(trimester[i]->getTrimesterNo())==acadademecianEditCourseChosenTrimester)
        {
            choosenTrimesterIndex = i;
            break;
        }
    }
    unsigned int editableCoursesIndex;
    for(unsigned int i=0;i<trimester[choosenTrimesterIndex]->getCourse().size();i++)
    {
        if(trimester[choosenTrimesterIndex]->getCourse()[i]->getCourseCode()==getCourseCode.toUtf8().constData())
        {
            editableCoursesIndex = i;
            break;
        }
    }
    //qDebug() << ui->acadEditCourseTableView->model()->data(ui->acadEditCourseTableView->model()->index(ui->acadEditCourseTableView->currentIndex().row(),0)).toString();
    //trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex] is our choosen course to edit;
    bool isSaved = true;
    if(db.open())
    {
        if(getCourseName.compare(trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->getCourseName())!=0)
        {
            QSqlQuery changeCourseName;
            changeCourseName.prepare("UPDATE \""+QString::fromStdString(trimester[choosenTrimesterIndex]->getTrimester())+"-"+QString::number(trimester[choosenTrimesterIndex]->getTrimesterNo())+"\" SET \"courseName\" = '"+QString::fromStdString(getCourseName)+"' WHERE \"courseCode\" = '"+getCourseCode+"'");
            bool execSuccs = changeCourseName.exec();
            if(execSuccs)
            {
                trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->setCourseName(getCourseName);
            }
            else
            {
                ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->acadEditCourseErrorLabel->setText("Unable to Change Course Name");
                isSaved = false;
            }
        }
        if(courseCredit>=1&&courseCredit<=9)
        {
            if(courseCredit!=trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->getCreditHours())
            {

                QSqlQuery changeCourseCredit;
                changeCourseCredit.prepare("UPDATE \""+QString::fromStdString(trimester[choosenTrimesterIndex]->getTrimester())+"-"+QString::number(trimester[choosenTrimesterIndex]->getTrimesterNo())+"\" SET \"creditHour\" = "+QString::number(courseCredit)+" WHERE \"courseCode\" = '"+getCourseCode+"'");
                bool execSuccs = changeCourseCredit.exec();
                if(execSuccs)
                {
                    trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->setCreditHours(courseCredit);

                }
                else
                {
                    ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                    ui->acadEditCourseErrorLabel->setText("Unable to Change Course Credit Hour");
                    isSaved = false;

                }
            }
        }
        else
        {
            isSaved = false;
            ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
            ui->acadEditCourseErrorLabel->setText("Enter Course Credit Hour between 1 to 9");
        }
        if((getCoursePreRequisite!="")&&(getCoursePreRequisite!=trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->getPreRequisite()))
        {
            QSqlQuery changeCoursePreRequisite;
            changeCoursePreRequisite.prepare("UPDATE \""+QString::fromStdString(trimester[choosenTrimesterIndex]->getTrimester())+"-"+QString::number(trimester[choosenTrimesterIndex]->getTrimesterNo())+"\" SET \"preRequisite\" = '"+QString::fromStdString(getCoursePreRequisite)+"' WHERE \"courseCode\" = '"+getCourseCode+"'");
            bool execSuccs = changeCoursePreRequisite.exec();
            if(execSuccs)
            {
                trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->setPreRequisite(getCoursePreRequisite);

            }
            else
            {
                ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->acadEditCourseErrorLabel->setText("Unable to Change Course Credit Hour");
                isSaved = false;
            }
        }
        if(status!=trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->checkIsOpen())
        {
            QSqlQuery changeCourseStatus;
            QString statusCheck = status ? "TRUE" : "FALSE";
            changeCourseStatus.prepare("UPDATE \""+QString::fromStdString(trimester[choosenTrimesterIndex]->getTrimester())+"-"+QString::number(trimester[choosenTrimesterIndex]->getTrimesterNo())+"\" SET \"isOpen\" = "+statusCheck+" WHERE \"courseCode\" = '"+getCourseCode+"'");
            bool execSuccs = changeCourseStatus.exec();
            if(execSuccs)
            {
                trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->setStatus(status);

            }
            else
            {
                ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->acadEditCourseErrorLabel->setText("Unable to Change Set Open or Close");
                isSaved = false;
            }
        }
        if(getCourseVenue!=trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->getCourseVenue())
        {
            QSqlQuery changeCourseVenue;
            changeCourseVenue.prepare("UPDATE \""+QString::fromStdString(trimester[choosenTrimesterIndex]->getTrimester())+"-"+QString::number(trimester[choosenTrimesterIndex]->getTrimesterNo())+"\" SET \"courseVenue\" = '"+QString::fromStdString(getCourseVenue)+"' WHERE \"courseCode\" = '"+getCourseCode+"'");
            bool execSuccs = changeCourseVenue.exec();
            if(execSuccs)
            {
                trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->setCourseVenue(getCourseVenue);

            }
            else
            {
                ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->acadEditCourseErrorLabel->setText("Unable to Change Venue");
                isSaved = false;
            }
        }
        if(getCourseTime!=trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->getCourseTime())
        {
            QSqlQuery changeCourseTime;
            changeCourseTime.prepare("UPDATE \""+QString::fromStdString(trimester[choosenTrimesterIndex]->getTrimester())+"-"+QString::number(trimester[choosenTrimesterIndex]->getTrimesterNo())+"\" SET \"courseTime\" = '"+QString::fromStdString(getCourseTime)+"' WHERE \"courseCode\" = '"+getCourseCode+"'");
            bool execSuccs = changeCourseTime.exec();
            if(execSuccs)
            {
                trimester[choosenTrimesterIndex]->getCourse()[editableCoursesIndex]->setCourseTime(getCourseTime);

            }
            else
            {
                ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : red; }");
                ui->acadEditCourseErrorLabel->setText("Unable to Change Time");
                isSaved = false;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Connection to database lost");
    }
    db.close();
    if(isSaved)
    {
        ui->acadEditCourseErrorLabel->setStyleSheet("QLabel { color : green; }");
        ui->acadEditCourseErrorLabel->setText("Changes Saved");
    }
    ui->acadEditCourseTableView->setModel(acadViewCourseTable(QString::fromStdString(acadademecianEditCourseChosenTrimester)));
}
void MainMenu::acadDeleteCourse()
{
    ui->acadDeleteFacultyLabel->setText("Faculty: "+QString::fromStdString(academician->getFaculty()->getFacultyFullName()));
    ui->acadDeleteTrimesterComboBox->clear();
    ui->acadDeleteTrimesterComboBox->addItem(currentTrimester);
    ui->acadDeleteTrimesterComboBox->addItem(upcomingTrimester);
    ui->acadDeleteTableView->verticalHeader()->setVisible(false);
    ui->acadDeleteTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->acadDeleteTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->acadDeleteTableView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->acadDeleteTableView->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");
    academecianDeleteCourseChoosenTrimester = ui->acadDeleteTrimesterComboBox->currentText().toUtf8().constData();

    ui->acadDeleteTrimesterComboBox->setCurrentText(QString::fromStdString(academecianDeleteCourseChoosenTrimester));
    ui->acadDeleteTableView->setModel(acadViewCourseTable(QString::fromStdString(academecianDeleteCourseChoosenTrimester)));
}
void MainMenu::on_acadDeleteTrimesterComboBox_activated(const QString &arg1)
{
    //ui->acadDeleteTableView->setCurrentIndex(ui->acadDeleteTableView->model()->index(0,0));
    //ui->acadDeleteTableView->selectionModel()->select(ui->acadDeleteTableView->model()->index(0,0), QItemSelectionModel::Select);
    academecianDeleteCourseChoosenTrimester=arg1.toUtf8().constData();
    ui->acadDeleteTableView->setModel(acadViewCourseTable(arg1));
}
void MainMenu::on_acadDeleteButton_clicked()
{
    //getting the selected course code from table
    std::string getCourseCode = ui->acadDeleteTableView->model()->data(ui->acadDeleteTableView->model()->index(ui->acadDeleteTableView->currentIndex().row(),0)).toString().toUtf8().constData();
    unsigned int tindex; // index for trimester
    int countTrimester=0; // redundant counting in case trimester does'nt match will not delete the course
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(trimester[i]->getTrimester()+"-"+std::to_string(trimester[i]->getTrimesterNo())==academecianDeleteCourseChoosenTrimester)
        {
            tindex = i;
            countTrimester++;
            break;
        }
    }
    int countCourse = 0; //redundant counting in case the course does'nt match in selected trimester, will not delete
    unsigned int cindex; // index for course
    for(unsigned int i=0;i<trimester[tindex]->getCourse().size();i++)
    {
        if(trimester[tindex]->getCourse()[i]->getCourseCode()==getCourseCode) // checking course
        {
            cindex = i;
            countCourse++;
            break;
        }
    }
    if(countCourse!=0&&countTrimester!=0) // in case selection is not made or not found the course program will skip deleting hence no crash
    {
        if(db.open()) // checking database
        {
            //getting the students in this course
            for(unsigned int i=0;i<trimester[tindex]->getCourse()[cindex]->getStudent().size();i++)
            {
                //and deleting the course in students database that he/she(academecian) will delete from the server.
                QSqlQuery deleteCourseFromStudent;
                deleteCourseFromStudent.prepare("DELETE FROM \""+QString::fromStdString(trimester[tindex]->getCourse()[cindex]->getStudent()[i]->getUserID())+"\" WHERE \"courseCode\"='"+QString::fromStdString(trimester[tindex]->getCourse()[cindex]->getCourseCode())+"'");
                deleteCourseFromStudent.exec();
                for(unsigned int j=0;j<trimester[tindex]->getCourse()[cindex]->getStudent()[i]->returnCourse().size();j++)
                {
                    //checking in students course list and deleting the selected course from student also
                    if(trimester[tindex]->getCourse()[cindex]->getStudent()[i]->returnCourse()[j]->getCourseCode()==trimester[tindex]->getCourse()[cindex]->getCourseCode())
                    {
                        //deleting here from memory.
                       trimester[tindex]->getCourse()[cindex]->getStudent()[i]->dropCourse(trimester[tindex]->getCourse()[cindex]);
                    }
                }
            }
            for(unsigned int i=0;i<trimester[tindex]->getCourse().size();i++)
            {
                // after deleting the course from student course's memory and database
                //now program will delete the course from the trimester it was created. both in database and memory
                QSqlQuery deleteCourseFromTrimester;
                deleteCourseFromTrimester.prepare("DELETE FROM \""+QString::fromStdString(trimester[tindex]->getTrimester())+"-"+QString::number(trimester[tindex]->getTrimesterNo())+"\" WHERE \"courseCode\"='"+QString::fromStdString(trimester[tindex]->getCourse()[cindex]->getCourseCode())+"'");
                deleteCourseFromTrimester.exec();
                trimester[tindex]->deleteCourse(i);
            }
            ui->acadDeleteErrorShow->setText("Course deleted");
        }
        else
        {
            QMessageBox::critical(this, "Database Error", "Database connection lost. No Course deleted");
        }
        db.close();
        ui->acadDeleteTableView->setModel(acadViewCourseTable(QString::fromStdString(academecianDeleteCourseChoosenTrimester)));
    }
}
void MainMenu::acadViewAllCourseAndStudent()
{
    ui->acadAllFacultyComboBox->clear();
    ui->acadAllTrimesterComboBox->clear();
    ui->acadAllCoursesComboBox->clear();
    viewAllSelectedFaculty="";
    ui->acadAcademicianNameLabel->clear();
    ui->acadCourseName->clear();
    ui->acadCreditHour->clear();
    ui->acadCoursePreRequiste->clear();
    ui->acadProgram->clear();
    ui->acadTime->clear();
    ui->acadVenue->clear();
    ui->acadAllView->clearSpans();
    ui->acadAllFacultyComboBox->addItem("Select Faculty");
    for(unsigned int i=0;i<faculty.size();i++)
    {
        ui->acadAllFacultyComboBox->addItem(QString::fromStdString(faculty[i]->getFacultyName()));
    }
    ui->acadAllFacultyComboBox->setCurrentText("Select Faculty");
}
void MainMenu::on_acadAllFacultyComboBox_activated(const QString &arg1)
{
    ui->acadAllTrimesterComboBox->clear();
    ui->acadAllCoursesComboBox->clear();
    ui->acadAcademicianNameLabel->clear();
    ui->acadCourseName->clear();
    ui->acadCreditHour->clear();
    ui->acadCoursePreRequiste->clear();
    ui->acadProgram->clear();
    ui->acadTime->clear();
    ui->acadVenue->clear();
    ui->acadAllView->clearSpans();
    ui->acadAllTrimesterComboBox->addItem("Select Trimester");
    for(unsigned int i=0;i<trimester.size();i++)
    {
        ui->acadAllTrimesterComboBox->addItem(QString::fromStdString(trimester[i]->getTrimester())+"-"+QString::number(trimester[i]->getTrimesterNo()));
    }
    ui->acadAllTrimesterComboBox->setCurrentText("Select Trimester");
    viewAllSelectedFaculty=arg1.toUtf8().constData();
}
void MainMenu::on_acadAllTrimesterComboBox_activated(const QString &arg1)
{
    ui->acadAllCoursesComboBox->clear();
    ui->acadAcademicianNameLabel->clear();
    ui->acadCourseName->clear();
    ui->acadCreditHour->clear();
    ui->acadCoursePreRequiste->clear();
    ui->acadProgram->clear();
    ui->acadTime->clear();
    ui->acadVenue->clear();
    ui->acadAllView->clearSpans();
    ui->acadAllCoursesComboBox->addItem("Select Course");
    unsigned int index;
    int count=0;
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(trimester[i]->getTrimester()+"-"+std::to_string(trimester[i]->getTrimesterNo())==arg1.toUtf8().constData())
        {
            count++;
            index=i;
            break;
        }
    }
    if(count!=0)
    {
        for(unsigned int i=0;i<trimester[index]->getCourse().size();i++)
        {
            if(trimester[index]->getCourse()[i]->getFaculty()->getFacultyName()==viewAllSelectedFaculty)
            {
                ui->acadAllCoursesComboBox->addItem(QString::fromStdString(trimester[index]->getCourse()[i]->getCourseCode()));
            }
        }

        ui->acadAllCoursesComboBox->setCurrentText("Select Course");
        viewAllSelectedTrimester=arg1.toUtf8().constData();
    }

}
void MainMenu::on_acadAllCoursesComboBox_activated(const QString &arg1)
{
    ui->acadAllView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->acadAllView->verticalHeader()->setVisible(false);
    ui->acadAllView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->acadAllView->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->acadAllView->setStyleSheet("QHeaderView::section { background-color:rgb(166, 255, 250)}");
    ui->acadAcademicianNameLabel->clear();
    ui->acadCourseName->clear();
    ui->acadCreditHour->clear();
    ui->acadCoursePreRequiste->clear();
    ui->acadProgram->clear();
    ui->acadTime->clear();
    ui->acadVenue->clear();
    ui->acadAllView->clearSpans();
    std::string getCourseCode = arg1.toUtf8().constData();
    unsigned int indexT;
    for(unsigned int i=0;i<trimester.size();i++)
    {
        if(trimester[i]->getTrimester()+"-"+std::to_string(trimester[i]->getTrimesterNo())==viewAllSelectedTrimester)
        {
            indexT=i;
            break;
        }
    }
    unsigned int indexCourse;
    int count=0;
    for(unsigned int i=0;i<trimester[indexT]->getCourse().size();i++)
    {
        if((trimester[indexT]->getCourse()[i]->getCourseCode()==getCourseCode)&&(trimester[indexT]->getCourse()[i]->getFaculty()->getFacultyName()==viewAllSelectedFaculty))
        {
            count++;
            indexCourse=i;
            break;
        }
    }
    if(count!=0)
    {
        ui->acadAcademicianNameLabel->setText("Academician: "+QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getAcademician()->getUserName()));
        ui->acadCourseName->setText("Course Name: "+QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getCourseName()));
        ui->acadCreditHour->setText("Credit Hour: "+QString::number(trimester[indexT]->getCourse()[indexCourse]->getCreditHours()));
        ui->acadCoursePreRequiste->setText("Pre-requsite: "+QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getPreRequisite()));
        UnderGraduateCourse* ugc=dynamic_cast<UnderGraduateCourse*>(trimester[indexT]->getCourse()[indexCourse]);
        if(ugc!=nullptr)
        {
            ui->acadProgram->setText("Program: "+QString::fromStdString(ugc->getProgramName()));
        }
        else
        {
            PostGraduateCourse* pgc=dynamic_cast<PostGraduateCourse*>(trimester[indexT]->getCourse()[indexCourse]);
            if(pgc!=nullptr)
            {
                ui->acadProgram->setText("Program: "+QString::fromStdString(pgc->getProgramName()));
            }
            else
            {
                DiplomaCourse* dc=dynamic_cast<DiplomaCourse*>(trimester[indexT]->getCourse()[indexCourse]);
                if(dc!=nullptr)
                {
                    ui->acadProgram->setText("Program: "+QString::fromStdString(dc->getProgramName()));
                }
                else
                {
                    ui->acadProgram->setText("Program: Unavailable");
                }
            }
        }

        ui->acadTime->setText("Time: "+QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getCourseTime()));
        ui->acadVenue->setText("Venue: "+QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getCourseVenue()));

        QStandardItemModel *model = new QStandardItemModel(0,2,this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Student ID")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Student Name")));

        QList<QStandardItem*> rowData;
        for(unsigned int i=0;i<trimester[indexT]->getCourse()[indexCourse]->getStudent().size();i++)
        {
            rowData.clear();
            rowData << new QStandardItem(QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getStudent()[i]->getUserID()));
            rowData << new QStandardItem(QString::fromStdString(trimester[indexT]->getCourse()[indexCourse]->getStudent()[i]->getUserName()));
            model->appendRow(rowData);
        }
        ui->acadAllView->setModel(model);
    }
}
void MainMenu::on_profile_triggered()
{
    //profile information view from memory
    ui->viewUserID->clear();
    ui->viewUserName->clear();
    ui->viewUserFaculty->clear();
    ui->viewUserGender->clear();
    ui->viewUserProgram->clear();
    ui->stackedWidget->setCurrentWidget(ui->viewUserInformation);
    if(currentLoggedInUser!=nullptr)
    {
        ui->viewUserID->setText("ID: "+QString::fromStdString(currentLoggedInUser->getUserID()));
        ui->viewUserName->setText("Name: "+QString::fromStdString(currentLoggedInUser->getUserName()));
        if(currentLoggedInUser->getUserGender()=='m')
        {
            ui->viewUserGender->setText("Gender: Male");
        }
        else
        {
            if(currentLoggedInUser->getUserGender()=='f')
            {
                ui->viewUserGender->setText("Gender: Female");
            }
        }
        Academician* acd = dynamic_cast<Academician*>(currentLoggedInUser);
        if(acd!=nullptr)
        {
            ui->viewUserFaculty->setText("Faculty: "+QString::fromStdString(acd->getFaculty()->getFacultyFullName()));
        }
        else
        {
            Student* std = dynamic_cast<Student*>(currentLoggedInUser);
            if(std!=nullptr)
            {
                ui->viewUserFaculty->setText("Faculty: "+QString::fromStdString(std->getFaculty()->getFacultyFullName()));
                UnderGraduate* ugs = dynamic_cast<UnderGraduate*>(std);
                if(ugs!=nullptr)
                {
                    ui->viewUserProgram->setText("Program: "+QString::fromStdString(ugs->getProgram()));
                }
                else
                {
                    PostGraduate* pgs = dynamic_cast<PostGraduate*>(std);
                    if(pgs!=nullptr)
                    {
                        ui->viewUserProgram->setText("Program: "+QString::fromStdString(pgs->getProgram()));
                    }
                    else
                    {
                        Diploma* ds = dynamic_cast<Diploma*>(std);
                        if(ds!=nullptr)
                        {
                            ui->viewUserProgram->setText("Program: "+QString::fromStdString(ds->getProgram()));
                        }
                    }
                }
            }
        }
    }

}
void MainMenu::on_exit_triggered()
{
    QApplication::quit(); //exiting program
}
