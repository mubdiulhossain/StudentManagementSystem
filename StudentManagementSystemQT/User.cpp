#include "User.h"

User::User()
{
    userName="Unavailable";
    userID="Unavailable";
    userPassword="Unavailable";
    userGender='n';
}
User::~User()
{
}
std::string User::getUserName() const
{
    return userName;
}
std::string User::getUserID() const
{
    return userID;
}
char User::getUserGender() const
{
    return userGender;
}
bool User::checkPassword(std::string userPassword) const
{
    if(this->userPassword==userPassword)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void User::setUserName(std::string userName)
{
    this->userName=userName;
}
void User::setUserID(std::string userID)
{
    this->userID=userID;
}
void User::setPassword(std::string userPassword)
{
    this->userPassword=userPassword;
}

void User::setUserGender(char userGender)
{
    this->userGender=userGender;
}
