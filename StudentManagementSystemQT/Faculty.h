#ifndef FACULTY_H
#define FACULTY_H

#include<string>
#include "Academician.h"
#include "Student.h"
#include<vector>

class Faculty
{
    public:
        Faculty();
        Faculty(std::string faculty_name);
        ~Faculty();
        std::string getFacultyName() const;//set faculty name(id)
        std::string getFacultyFullName() const;//get faculty full name
        void setFacultyName(std::string faculty_name); //set faculty name(id)
        void setFacultyFullName(std::string facultyFullName); //set faculty full name

        std::vector<Academician*> getAcademician();//get academician list
        void addAcademician(Academician*);
        std::vector<Student*> getStudent(); //get student list
        void addStudent(Student*);

        void FacultyUser();
        void showDetails();
    private:

        std::string faculty_name;
        std::vector<Academician*> academician; //list of academicians
        std::vector<Student*> student;//list of students
        std::string facultyFullName;
};

#endif // FACULTY_H
