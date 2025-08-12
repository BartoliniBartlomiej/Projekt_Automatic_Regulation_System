#ifndef REGULATOR_HPP
#define REGULATOR_HPP

#include "Pomieszczenie.hpp"
#include "Grzejnik.hpp"
#include <stdexcept>

class Regulator
{
public:
    ~Regulator() {}
    void ustawPomieszczenie(Pomieszczenie* p)
    {
        pomieszczenie = p;
    }
        
    void ustawGrzejnik(Grzejnik* g)
    {
        grzejnik = g;
    }
    virtual void steruj(float wartoscZadana, float dt) = 0;
    //virtual void steruj(float wartoscZadana, float dt) = 0;
    virtual bool czySkonfigurowany() const = 0;
protected:
    Pomieszczenie* pomieszczenie;
    Grzejnik* grzejnik;
};


#endif // REGULATOR_HPP
