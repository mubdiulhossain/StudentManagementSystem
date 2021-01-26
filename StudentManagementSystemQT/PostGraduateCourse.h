#ifndef POSTGRADUATECOURSE_H
#define POSTGRADUATECOURSE_H

#include <Course.h>


class PostGraduateCourse : public Course
{
    public:
        PostGraduateCourse();
        ~PostGraduateCourse() override;
        void viewCourseInfo() override;
        std::string getProgramName() const;//get program
    private:
        std::string courseProgram = "Postgraduate";
};

#endif // POSTGRADUATECOURSE_H
