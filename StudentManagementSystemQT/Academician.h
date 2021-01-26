#ifndef ACADEMICIAN_H
#define ACADEMICIAN_H

//Includeing neccessary headers
#include <User.h>
#include <Course.h>
#include <UnderGraduateCourse.h>
#include <DiplomaCourse.h>
#include <PostGraduateCourse.h>
#include <vector>
#include <Trimester.h>

class Academician : public User //academician is a child of parent class user
{
    public:
        Academician(); // constructor
        ~Academician();// destructor
        //create course is method to create courses.
        void createCourse(std::string courseCode, std::string courseName, int creditHour, std::string preRequsite, bool isOpen, std::string courseVenue, std::string courseTime, std::string courseProgram,Trimester* t);
        void details();
        Faculty* getFaculty() const;
        void setFaculty(Faculty*);
    private:
        Faculty* f; //1 academician has only one faculty
};

#endif // ACADEMICIAN_H
