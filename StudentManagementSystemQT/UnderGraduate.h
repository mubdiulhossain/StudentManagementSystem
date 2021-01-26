#ifndef UNDERGRADUATE_H
#define UNDERGRADUATE_H

#include <Student.h>
#include <UnderGraduateCourse.h>
#include <Trimester.h>
#include <QDebug>
class UnderGraduate : public Student
{
    public:
        UnderGraduate();
        ~UnderGraduate() override;
        void details() override;
        int registerCourse(Course*);
        std::string getProgram() const;

    private:
        std::string program;
};
#endif // UNDERGRADUATE_H
