#ifndef STUDENT_H
#define STUDENT_H

#include <User.h>
#include <Course.h>
#include <Trimester.h>
//#include <Faculty.h>
class Faculty;
class Trimester;
class Student : public User
{
    public:
        Student();
        ~Student();
        virtual void showRegisteredCourse();

        bool dropCourse(Course*); //drop course
        void details();
        void setFaculty(Faculty*); //setting faculty pointer
        Faculty* getFaculty() const;
        void addCourse(Course* c); //adding course
        void addTrimester(std::string);
        std::vector<std::string> getTakenTrimester() const; //get list of string trimester taken
        std::vector<Course*> returnCourse() const; //get list of course
    private:
        Faculty *f; //students faculty object
        std::vector<std::string> trimesterTaken; //string list of student trimester. stored as yy/yy-#
        std::vector<Course*> courses; //course lists taken by the student
};
#endif // STUDENT_H
