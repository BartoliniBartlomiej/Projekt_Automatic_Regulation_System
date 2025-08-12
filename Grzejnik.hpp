#ifndef GRZEJNIK_HPP
#define GRZEJNIK_HPP

#include <stdio.h>
#include <iostream>

class Grzejnik 
{
public:
    Grzejnik(float mocNominalna) : mocNominalna(mocNominalna), poziomMocy(0.0f) {}

    void ustawPoziomMocy(float poziom) 
    {
        if (poziom < 0.0f || poziom > 1.0f) 
        {
            throw std::invalid_argument("Poziom mocy musi być w zakresie od 0 do 1");
        }
        poziomMocy = poziom;
    }
    
    float obliczCieplo() const 
    {
        return poziomMocy * mocNominalna;
    }
    float getMocNominalna() {return mocNominalna;}
private:
    const float mocNominalna;
    float poziomMocy;
};

#endif // GRZEJNIK_HPP
