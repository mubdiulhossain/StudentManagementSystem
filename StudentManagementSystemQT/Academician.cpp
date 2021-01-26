#include "Academician.h"
//#include<iostream>
Academician::Academician()
{
    f=nullptr;
}
Academician::~Academician()
{

}
void Academician::setFaculty(Faculty* f)
{
    this->f=f; //assigning faculty to academician's faculty
}
void Academician::createCourse(std::string courseCode, std::string courseName, int creditHour, std::string preRequsite, bool isOpen, std::string courseVenue, std::string courseTime, std::string courseProgram, Trimester* t)
{
    Course* c;
    if(courseProgram=="UnderGraduate") //program checks the course program that has been entered
    {
        c = new UnderGraduateCourse(); //then creates a new course by its respective program class
        c->setCourseCode(courseCode);
        c->setCourseName(courseName);
        c->setCreditHours(creditHour);
        if(preRequsite.empty()) //checking if the entered prerequisite is empty
        {
            c->setPreRequisite(""); //if its empty program will set the prerequisite as null string
        }
        else
        {
            c->setPreRequisite(preRequsite); //else the prerequiste will be set as entered
        }
        c->setAcademician(this); //program will assign the current academician as the academician for the course
        c->setCourseVenue(courseVenue);
        c->setCourseTime(courseTime);
        c->setStatus(isOpen);
        c->setFaculty(getFaculty()); //assigning the academician's faculty to the course
        c->setTrimester(t); //assinging trimester for the course created
        t->addCourse(c); //and adding the created course to the trimester
    }
    else
    {
        if(courseProgram=="PostGraduate") //the procedure is same as undergraduate course
        {
            c = new PostGraduateCourse();
            c->setCourseCode(courseCode);
            c->setCourseName(courseName);
            c->setCreditHours(creditHour);
            if(preRequsite.empty())
            {
                c->setPreRequisite("");
            }
            else
            {
                c->setPreRequisite(preRequsite);
            }
            c->setAcademician(this);
            c->setCourseVenue(courseVenue);
            c->setCourseTime(courseTime);
            c->setStatus(isOpen);
            c->setFaculty(getFaculty());
            c->setTrimester(t);
            t->addCourse(c);

        }
        else
        {
            if(courseProgram=="Diploma") //the procedure is same as undergraduate course
            {
                c = new DiplomaCourse();
                c->setCourseCode(courseCode);
                c->setCourseName(courseName);
                c->setCreditHours(creditHour);
                if(preRequsite.empty())
                {
                    c->setPreRequisite("");
                }
                else
                {
                    c->setPreRequisite(preRequsite);
                }
                c->setAcademician(this);
                c->setCourseVenue(courseVenue);
                c->setCourseTime(courseTime);
                c->setStatus(isOpen);
                c->setFaculty(getFaculty());
                c->setTrimester(t);
                t->addCourse(c);
            }
        }
    }
}
void Academician::details()
{

}
Faculty* Academician::getFaculty() const
{
    return f; //returning academicians faculty object that cannot be modified because it is a const method
}
