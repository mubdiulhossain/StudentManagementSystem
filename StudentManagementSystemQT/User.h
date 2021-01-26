#ifndef USER_H
#define USER_H
#include<iostream>

class User //abstract class user
{
    public:
        User();
        virtual ~User();
        //accessor and mutator for User
        std::string getUserName() const;
        std::string getUserID() const;
        char getUserGender() const;
        bool checkPassword(std::string userPassword) const;

        void setUserName(std::string userName);
        void setUserID(std::string userID);
        void setPassword(std::string userPassword);
        void setFacultyName(std::string facultyName);
        void setUserGender(char userGender);

        virtual void details()=0; //making user an abstract class
    private:

        std::string userName;
        std::string userID;
        std::string userPassword;
        char userGender;
};

#endif // USER_H
