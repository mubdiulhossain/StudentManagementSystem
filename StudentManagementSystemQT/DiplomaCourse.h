#ifndef DIPLOMACOURSE_H
#define DIPLOMACOURSE_H

#include <Course.h>


class DiplomaCourse : public Course
{
    public:
        DiplomaCourse();
        ~DiplomaCourse() override;
        void viewCourseInfo() override;
        std::string getProgramName() const;//get program
    private:
        std::string courseProgram = "Diploma";
};

#endif // DIPLOMACOURSE_H
