#include "Trimester.h"

Trimester::Trimester()
{
    trimester="Unavailable";
    isOpen=false;
    trimesterNo=0;
    status = "null";
    //c = new Course();
}
Trimester::~Trimester()
{
    sc.clear();//clear course
}
void Trimester::deleteCourse(unsigned int index)
{
    sc.erase(sc.begin()+index);//erasing trimester by index
}
std::string Trimester::getTrimester() const
{
    return trimester;
}
void Trimester::setTrimester(std::string trimester)
{
    this->trimester=trimester;
}
std::vector<Course*> Trimester::getCourse() const
{
    return sc;
}
void Trimester::addCourse(Course* c)
{
    sc.emplace_back(c);//moving course to list
}
bool Trimester::checkIsOpen() const
{
    return isOpen;
}
void Trimester::setStatus(bool isOpen)
{
    this->isOpen=isOpen;
}
int Trimester::getTrimesterNo() const
{
    return trimesterNo;
}
std::string Trimester::getActivity() const
{
    return status;
}
void Trimester::setActivity(std::string status)
{
    this->status=status;
}
