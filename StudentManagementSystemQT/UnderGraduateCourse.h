#ifndef UNDERGRADUATECOURSE_H
#define UNDERGRADUATECOURSE_H

#include <Course.h>

class UnderGraduateCourse : public Course
{
    public:
        UnderGraduateCourse();
        ~UnderGraduateCourse() override;
        void viewCourseInfo() override;
        std::string getProgramName() const;//get program
    private:
        std::string courseProgram;

};
#endif // UNDERGRADUATECOURSE_H
