#ifndef TRIMESTER1_H
#define TRIMESTER1_H

#include <Trimester.h>

//trimester 1 class for an year
class Trimester1 : public Trimester
{
    public:
        Trimester1();
        ~Trimester1();
        int getTrimesterNo() const;
        std::string getTrimesterYear() const;
    private:
        int trimesterNo;
};

#endif // TRIMESTER1_H
