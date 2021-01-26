#include "Admin.h"

Admin::Admin()
{
    //ctor
}

Admin::~Admin()
{
    //dtor
}
Admin &Admin::getInstance() //admin is a singleton class
{
    static Admin admin; //creating a static Admin object
    return admin; // and returning it
}
void Admin::details()
{

}
Trimester* Admin::addTrimester(std::string trimesterYear, bool isOpen, std::string status, int trimesterNo)
{
    if(trimesterNo==1)  //checking trimester number to create an object for the respective class trimester1
    {
        Trimester* t;
        t = new Trimester1();
        t->setTrimester(trimesterYear);
        t->setStatus(isOpen);
        t->setActivity(status);
        return t;
    }
    else
    {
        if(trimesterNo==2) //same as trimester 1. except the new trimester is trimester2
        {
            Trimester* t;
            t = new Trimester2();
            t->setTrimester(trimesterYear);
            t->setStatus(isOpen);
            t->setActivity(status);
            return t;
        }
        else
        {
            if(trimesterNo==3) //same as trimester 1. except the new trimester is trimester3
            {
                Trimester* t = new Trimester3();
                t->setTrimester(trimesterYear);
                t->setStatus(isOpen);
                t->setActivity(status);
                return t;
            }
        }
    }
    return nullptr;
}
Faculty* Admin::createFaculty(std::string id,std::string name) //creating new faculty
{
    Faculty* f = new Faculty();
    f->setFacultyName(id);
    f->setFacultyFullName(name);
    return f;
}
User* Admin::createUser(std::string userName, std::string userID, std::string userPassword, std::string userType,char g,Faculty* f)
{
    if(userType.compare("Academician")==0) //creating user by admin. usertype checks the type of the user
    {
        Academician* u = new Academician(); //in this case it's Academician so new Academician object is created
        u->setUserID(userID);
        u->setUserName(userName);
        u->setPassword(userPassword);
        u->setUserGender(g);
        u->setFaculty(f);
        return  u;
    }
    else
    {
        if(userType.compare("UnderGraduate")==0) //program will directly create UnderGraduate student by checking the userType
        {
            Student* u = new UnderGraduate();
            u->setUserID(userID);
            u->setUserName(userName);
            u->setPassword(userPassword);
            u->setUserGender(g);
            u->setFaculty(f);
            return u;
        }
        else
        {
            if(userType.compare("PostGraduate")==0)
            {
                Student* u = new PostGraduate();
                u->setUserID(userID);
                u->setUserName(userName);
                u->setPassword(userPassword);
                u->setUserGender(g);
                u->setFaculty(f);
                return u;
            }
            else
            {
                if(userType.compare("Diploma")==0)
                {
                    Student* u = new Diploma();
                    u->setUserID(userID);
                    u->setUserName(userName);
                    u->setPassword(userPassword);
                    u->setUserGender(g);
                    u->setFaculty(f);
                    return u;
                }
            }
        }
    }
    return nullptr;
}
