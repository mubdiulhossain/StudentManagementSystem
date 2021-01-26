#ifndef ADMIN_H
#define ADMIN_H

#include <User.h>
#include <UnderGraduate.h>
#include <PostGraduate.h>
#include <Diploma.h>
#include <Academician.h>
#include <Faculty.h>
#include <vector>
#include <Trimester.h>
#include <Trimester1.h>
#include <Trimester2.h>
#include <Trimester3.h>

class Admin : public User
{
    public:
        ~Admin();
        User* createUser(std::string, std::string, std::string, std::string,char,Faculty*);
        Trimester* addTrimester(std::string trimesterYear, bool isOpen, std::string status, int trimesterNo);
        void details();

        static Admin& getInstance(); //admin is a singleton class
        Faculty* createFaculty(std::string,std::string); //create faculty by admin
    private:
        Admin(); //setting admin as private to be a singleton class

};

#endif // ADMIN_H
