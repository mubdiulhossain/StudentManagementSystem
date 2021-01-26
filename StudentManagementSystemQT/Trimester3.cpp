#include "Trimester3.h"

Trimester3::Trimester3()
{
    trimesterNo=3;
}

Trimester3::~Trimester3()
{
    //dtor
}
int Trimester3::getTrimesterNo() const
{
    return trimesterNo;
}
std::string Trimester3::getTrimesterYear() const
{
    return getTrimester();
}
