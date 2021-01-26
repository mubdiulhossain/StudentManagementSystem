#ifndef TRIMESTER2_H
#define TRIMESTER2_H

#include <Trimester.h>

//trimester 2 class for an year
class Trimester2 : public Trimester
{
    public:
        Trimester2();
        ~Trimester2();
        //void getTrimester2(std::string);
        int getTrimesterNo() const;
        std::string getTrimesterYear() const;
    private:
        int trimesterNo;
};

#endif // TRIMESTER2_H
