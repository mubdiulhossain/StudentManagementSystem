#ifndef DIPLOMA_H
#define DIPLOMA_H

#include <Student.h>
#include <vector>
#include <Trimester.h>
//diploma course
class Diploma : public Student
{
    public:
        Diploma();
        ~Diploma();
        void details();
        std::string getProgram() const;
        int registerCourse(Course*);
    private:
        std::string program;
};

#endif // DIPLOMA_H
