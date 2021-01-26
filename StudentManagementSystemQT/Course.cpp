#include "Course.h"

Course::Course()
{
    courseName="Unavailable";
    courseCode="Unavailable";
    courseTime="Unavailable";
    courseVenue="Unavailable";
    creditHours=0;
    preRequisite="Unavailable";
    //setting memory to null pointer
    academicianInCharge = nullptr;
    courseFaculty=nullptr;
    trimester = nullptr;
    isOpen=false;
}

Course::~Course()
{
    student.clear();//clearing student list
}
std::string Course::getCourseName() const
{
    return courseName;
}
std::string Course::getCourseCode() const
{
    return courseCode;
}
int Course::getCreditHours() const
{
    return creditHours;
}
std::string Course::getPreRequisite() const
{
    return preRequisite;
}
Academician* Course::getAcademician() const
{
    return academicianInCharge;//returning course academician pointer
}
std::vector<Student*> Course::getStudent() const
{
    return student;//returning student list
}
std::string Course::getCourseVenue() const
{
    return courseVenue;
}
std::string Course::getCourseTime() const
{
    return courseTime;
}
Faculty* Course::getFaculty() const
{
    return courseFaculty;//returning course faculty pointer
}
void Course::setCourseName(std::string courseName)
{
    this->courseName=courseName;
}
void Course::setCourseCode(std::string courseCode)
{
    this->courseCode=courseCode;
}
void Course::setCreditHours(int creditHours)
{
    this->creditHours=creditHours;
}
void Course::setAcademician(Academician *academicianInCharge)
{
    this->academicianInCharge=academicianInCharge;
}
void Course::addStudent(Student* s)
{
    student.emplace_back(s);
}
void Course::setCourseVenue(std::string courseVenue)
{
    this->courseVenue=courseVenue;
}
void Course::setCourseTime(std::string courseTime)
{
    this->courseTime=courseTime;
}
void Course::setPreRequisite(std::string preRequisite)
{
    this->preRequisite=preRequisite;
}
void Course::setFaculty(Faculty *courseFaculty)
{
    this->courseFaculty=courseFaculty;
}
void Course::viewCourseInfo()
{

}
bool Course::checkIsOpen() const
{
    return isOpen;
}
void Course::setStatus(bool isOpen)
{
    this->isOpen=isOpen;
}
Trimester* Course::getTrimester() const
{
    return trimester;//returning course trimester pointer
}
void Course::setTrimester(Trimester* trimester)
{
    this->trimester=trimester;
}
void Course::removeStudent(unsigned int index)
{
    student.erase(student.begin()+index);
}
