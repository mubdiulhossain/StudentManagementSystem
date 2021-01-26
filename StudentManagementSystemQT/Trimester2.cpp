#include "Trimester2.h"

Trimester2::Trimester2()
{
    trimesterNo=2;
}

Trimester2::~Trimester2()
{
    //dtor
}
int Trimester2::getTrimesterNo() const
{
    return trimesterNo;
}
std::string Trimester2::getTrimesterYear() const
{
    return getTrimester();
}
