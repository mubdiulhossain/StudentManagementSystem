#ifndef TRIMESTER3_H
#define TRIMESTER3_H

#include <Trimester.h>

//trimester 3 class for an year
class Trimester3 : public Trimester
{
    public:
        Trimester3();
        ~Trimester3();
        //void getTrimester3(std::string);
        int getTrimesterNo() const;
        std::string getTrimesterYear() const;
    private:
        int trimesterNo;
};

#endif // TRIMESTER3_H
