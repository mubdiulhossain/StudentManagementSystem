#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
#include <vector>
class Faculty; //course has faculty.
class Academician; //course has academician
class Student; //course has many students
class Trimester; //one course has one trimester
class Course
{
    public:
        Course();
        virtual ~Course();
        std::string getCourseName() const;
        std::string getCourseCode() const;
        int getCreditHours() const;
        std::string getPreRequisite() const;
        Academician* getAcademician() const;//get course academician object
        std::vector<Student*> getStudent() const;//get list of students in this course
        void removeStudent(unsigned int);//remove a student
        std::string getCourseVenue() const;
        std::string getCourseTime() const;
        Faculty* getFaculty() const;//get course faculty object
        Trimester* getTrimester() const;//get course trimester object
        bool checkIsOpen() const;

        void setTrimester(Trimester*);//set course trimester object
        void setStatus(bool isOpen);
        void setCourseName(std::string courseName);
        void setCourseCode(std::string courseCode);
        void setCreditHours(int creditHours);
        void setAcademician(Academician *academicianInCharge);//set course academician object
        void addStudent(Student* s);//Add students to the student list
        void setCourseVenue(std::string courseVenue);
        void setCourseTime(std::string courseTime);
        void setPreRequisite(std::string preRequisite);
        void setFaculty(Faculty *courseFaculty);//set course faculty object
        virtual void viewCourseInfo();

    private:
        std::string courseName;
        std::string courseCode;
        int creditHours;
        std::string preRequisite;
        Academician* academicianInCharge;
        bool isOpen;

        std::string courseVenue;
        std::string courseTime;
        Faculty* courseFaculty ;
        std::vector<Student*> student;//student list
        Trimester* trimester;
};

#endif // COURSE_H
