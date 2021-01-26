#include "Diploma.h"

Diploma::Diploma()
{
    program = "Diploma";
}
Diploma::~Diploma()
{
    //dtor
}
/*void Diploma::registerCourse(const std::vector<Course*>& v)
{

}*/
void Diploma::details()
{
    std::cout<<"Student Name: "<<getUserName()<<std::endl;
    std::cout<<"ID: "<<getUserID()<<std::endl;
    //std::cout<<"Faculty: "<<getFacultyName()<<std::endl;
    std::cout<<"Program: "<<program;
}
std::string Diploma::getProgram() const
{
    return program;
}
int Diploma::registerCourse(Course* c)
{
    for(unsigned int i=0;i<returnCourse().size();i++)
    {
        if(c->getCourseCode()==returnCourse()[i]->getCourseCode())
        {
            return 1; // course already taken
        }
    }

    if(c->getPreRequisite()!="")
    {
        int count=0;
        for(unsigned int i=0;i<returnCourse().size();i++)
        {
            if(c->getPreRequisite().compare(returnCourse()[i]->getCourseCode())==0)
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
        if((returnCourse()[i]->getTrimester()->getTrimester()+"-"+std::to_string(returnCourse()[i]->getTrimester()->getTrimesterNo()))==(c->getTrimester()->getTrimester()+"-"+std::to_string(c->getTrimester()->getTrimesterNo())))
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
        addCourse(c); //
        return 0;
    }
}
