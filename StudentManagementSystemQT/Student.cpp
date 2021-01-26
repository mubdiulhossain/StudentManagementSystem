#include "Student.h"

Student::Student()
{
    //f=nullptr;
}
Student::~Student()
{
    //clearing trimester taken and courses
    trimesterTaken.clear();
    courses.clear();
}
void Student::showRegisteredCourse() // was used during std input output until qt ui
{
    //std::cout<<"Base class virtual function"<<std::endl;
}
void Student::setFaculty(Faculty *f)
{
    this->f=f;
}
Faculty* Student::getFaculty() const
{
    return f;
}
void Student::details()// was used during std input output until qt ui
{
    std::cout<<"Student Name: "<<getUserName()<<std::endl;
    std::cout<<"ID: "<<getUserID()<<std::endl;
    //std::cout<<"Faculty: "<<getFacultyName()<<std::endl;
    //std::cout<<"Program: "<<program<<std::endl;
}
bool Student::dropCourse(Course* c) //dropping course
{
    for(unsigned int i=0;i<c->getStudent().size();i++)
    {
        if(c->getStudent()[i]->getUserID()==getUserID()) //checking user id
        {
            c->removeStudent(i);
            break;
        }
    }
    for(unsigned int i=0;i<courses.size();i++)
    {
        if(c->getCourseCode()==courses[i]->getCourseCode()) //checking course code
        {
            courses.erase(courses.begin()+i); //removing it
            return true; //returning true is done removing
        }
    }
    return false;
}
void Student::addCourse(Course* c)
{

    courses.emplace_back(c); //adding course

}
std::vector<Course*> Student::returnCourse() const
{
    return courses; //returning course
}
void Student::addTrimester(std::string trimestert)
{
    trimesterTaken.push_back(trimestert); //adding string trimesters
}
std::vector<std::string> Student::getTakenTrimester() const
{
    return trimesterTaken; //returning trimester
}
