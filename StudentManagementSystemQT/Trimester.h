#ifndef TRIMESTER_H
#define TRIMESTER_H

#include<string>
#include<vector>
#include<Course.h>


class Trimester
{
    public:
        Trimester(); //Constructor
        virtual ~Trimester();//Virtual distructor
        std::string getTrimester() const;//Get trimester year
        std::vector<Course*> getCourse() const;//Get list of courses
        bool checkIsOpen() const;//Check status
        virtual int getTrimesterNo() const;//Get trimester No
        void deleteCourse(unsigned int);//Delete course
        void setStatus(bool isOpen);//set status
        void setTrimester(std::string trimester);//set trimester year
        void addCourse(Course*);//Add course
        std::string getActivity() const;//Activity
        void setActivity(std::string);//Set activity

    private:
        std::string trimester;
        std::string status;
        int trimesterNo;
        bool isOpen;
        std::vector<Course*> sc;//student course list
};

#endif // TRIMESTER_H
