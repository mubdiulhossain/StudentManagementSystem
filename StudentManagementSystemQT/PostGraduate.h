#ifndef POSTGRADUATE_H
#define POSTGRADUATE_H

#include <Student.h>
#include <Course.h>
#include <PostGraduateCourse.h>
#include <vector>
#include <typeinfo>
//#include <Trimester.h>

class PostGraduate : public Student
{
    public:
        PostGraduate();
        std::string getProgram() const;
        ~PostGraduate();
        int registerCourse(Course*);
        void details();
//        void registerCourse(const std::vector<Trimester*>&);
    private:
        std::string program;
};

#endif // POSTGRADUATE_H
