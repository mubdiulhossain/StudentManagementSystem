#include "PostGraduateCourse.h"

PostGraduateCourse::PostGraduateCourse()
{
    //ctor
}

PostGraduateCourse::~PostGraduateCourse()
{
    //dtor
}
std::string PostGraduateCourse::getProgramName() const
{
    return courseProgram; //returning program
}
void PostGraduateCourse::viewCourseInfo()//this method was used for std input output until QT ui
{
    std::cout<<"Course Name: "<<getCourseName()<<std::endl;
    std::cout<<"Course Code: "<<getCourseCode()<<std::endl;
    std::cout<<"Credit Hours: "<<getCreditHours()<<std::endl;
    std::cout<<"Academician Name: "<<getAcademician()<<std::endl;
    std::cout<<"Venue: "<<getCourseVenue()<<std::endl;
    std::cout<<"Time: "<<getCourseTime()<<std::endl;
    std::cout<<"Program: "<<courseProgram<<std::endl;
}
