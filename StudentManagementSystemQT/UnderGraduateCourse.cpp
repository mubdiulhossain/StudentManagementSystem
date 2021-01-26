#include "UnderGraduateCourse.h"
class UnderGraduate;
UnderGraduateCourse::UnderGraduateCourse()
{
    courseProgram = "UnderGraduate";
}
UnderGraduateCourse::~UnderGraduateCourse()
{
    //dtor
}
std::string UnderGraduateCourse::getProgramName() const
{
    return courseProgram;//returning program
}
void UnderGraduateCourse::viewCourseInfo()//this method was used for std input output until QT ui
{
    std::cout<<getCourseName()<<"\t\t"<<getCourseCode()<<"\t\t"<<getCreditHours()<<"\t\t"<<getAcademician()<<"\t\t"<<getCourseVenue()<<"\t\t"<<getCourseTime()<<"\t"<<getFaculty()<<std::endl;
}
