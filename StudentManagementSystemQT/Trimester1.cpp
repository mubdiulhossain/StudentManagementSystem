#include "Trimester1.h"

Trimester1::Trimester1()
{
    trimesterNo=1;
}

Trimester1::~Trimester1()
{
    //dtor
}
int Trimester1::getTrimesterNo() const
{
    return trimesterNo;
}
std::string Trimester1::getTrimesterYear() const
{
    return getTrimester();
}
