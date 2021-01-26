#include "UnderGraduate.h"

UnderGraduate::UnderGraduate()
{
    program = "UnderGraduate";
}
UnderGraduate::~UnderGraduate(){}
int UnderGraduate::registerCourse(Course* c)
{
    for(unsigned int i=0;i<returnCourse().size();i++)
    {
        if(c->getCourseCode()==returnCourse()[i]->getCourseCode()) //checking if the course matches with previous taken courses
        {
            return 1; // course already taken
        }
    }

    if(c->getPreRequisite()!="")
    {
        int count=0;
        for(unsigned int i=0;i<returnCourse().size();i++)
        {
            if(c->getPreRequisite().compare(returnCourse()[i]->getCourseCode())==0) //checking if the course's pre requisite has been taken or not
            {
                count++;
                break;
            }
        }
        if(count==0)
        {
            return 2; // prerequisite not taken
        }
    }
    int countCredit=0;
    for(unsigned int i=0;i<returnCourse().size();i++)
    {
        if((returnCourse()[i]->getTrimester()->getTrimester()+"-"+std::to_string(returnCourse()[i]->getTrimester()->getTrimesterNo()))==(c->getTrimester()->getTrimester()+"-"+std::to_string(c->getTrimester()->getTrimesterNo()))) //counting total credit taken on that particular trimister
        {
            countCredit = countCredit+returnCourse()[i]->getCreditHours();
        }
    }
    int creditTaken = countCredit+c->getCreditHours();
    if(creditTaken>22)
    {
        return 3; //  22 credit already taken
    }
    else
    {
        qDebug() << c->checkIsOpen();
        if(c->checkIsOpen())
        {
            addCourse(c); // checking if course is open. if yes adds.
            return 0;
        }
        else
        {
            return 4; //if course is closed cannot register.
        }

    }
}


void UnderGraduate::details()
{
    std::cout<<"Student Name: "<<getUserName()<<std::endl;
    std::cout<<"ID: "<<getUserID()<<std::endl;
    //std::cout<<"Faculty: "<<getFacultyName()<<std::endl;
    std::cout<<"Program: "<<program<<std::endl;
}
std::string UnderGraduate::getProgram() const
{
    return program;
}
