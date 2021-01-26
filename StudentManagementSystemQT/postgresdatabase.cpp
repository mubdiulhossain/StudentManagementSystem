#include "postgresdatabase.h"

PostgresDatabase::PostgresDatabase(QString hostName, QString databaseName, QString dbUserName, QString dbpassword, int port)
{
    db = QSqlDatabase::addDatabase("QPSQL"); //creating database driver for PostgreSql
    //database setting
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(dbUserName);
    db.setPassword(dbpassword);
    db.setPort(port);
}
User *PostgresDatabase::getUser(QString username, QString userPassword)
{
    QSqlQuery qryUser("SELECT *  FROM \"User\" WHERE userID='"+username+"' and userPassword='"+userPassword+"'");
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

        QSqlQuery qryFaculty("SELECT *  FROM \"Faculty\" WHERE facultyName='"+QString::fromStdString(facultyName)+"'");
        Faculty* f = new Faculty(); //creating new faculty object
        while(qryFaculty.next())
        {
            f->setFacultyName(qryFaculty.value(0).toString().toUtf8().constData());
            f->setFacultyFullName(qryFaculty.value(1).toString().toUtf8().constData());
        }
        if(userType=="Admin") //checking user type
        {
            Admin* admin = &Admin::getInstance();
            countAdmin++;
            if(countAdmin<=1)
            {
                admin->setUserID(userID);
                admin->setUserName(userName);
                admin->setPassword(password);
                admin->setUserGender(userGender);
                return admin;
            }
        }
        else
        {
            if(userType=="Academician") //checking user type
            {
                Academician* u = new Academician(); //creating new academician object
                //setting academician
                u->setUserID(userID);
                u->setUserName(userName);
                u->setPassword(password);
                u->setUserGender(userGender);
                u->setFaculty(f);
                return u;
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
                    u1->setFaculty(f);
                    return u1;
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
                        u2->setFaculty(f);
                        return u2;
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
                            u3->setFaculty(f);
                            return u3;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}
bool PostgresDatabase::databaseOpen()
{
    return db.open();
}
void PostgresDatabase::databaseClose()
{
    db.close();
}
