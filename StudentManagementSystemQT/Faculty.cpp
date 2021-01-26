#include "Faculty.h"

Faculty::Faculty()
{
    faculty_name="Unavailable";
    facultyFullName="Unavailable";
}
Faculty::Faculty(std::string faculty_name)
{
    this->faculty_name=faculty_name;
}
void Faculty::setFacultyName(std::string faculty_name)
{
    this->faculty_name=faculty_name;
}
std::string Faculty::getFacultyName() const
{
    return faculty_name;
}
void Faculty::setFacultyFullName(std::string facultyFullName)
{
    this->facultyFullName=facultyFullName;
}
std::string Faculty::getFacultyFullName() const
{
    return facultyFullName;
}
std::vector<Academician*> Faculty::getAcademician()
{
    return academician; //returing list of academicians
}
void Faculty::addAcademician(Academician* u)
{
    academician.emplace_back(u); //moving and adding a academician object pointer to academician list
}
std::vector<Student*> Faculty::getStudent()
{
    return student; //returing list of students
}
void Faculty::addStudent(Student* u)
{
    student.emplace_back(u); //moving and adding a student object pointer to Student list
}
Faculty::~Faculty()
{
    //clearing students and academicians
    academician.clear();
    student.clear();
}
