#ifndef REGULATORBB_HPP
#define REGULATORBB_HPP

#include "Regulator.hpp"

class RegulatorBB : public Regulator
{
public:
    void steruj(float wartoscZadana, float dt) override
    {
        if (!czySkonfigurowany())
        {
            throw std::runtime_error("RegulatorBB nie jest skonfigurowany.");
        }
        float wartoscZmierzona = pomieszczenie->getTemperatura(); //dostep do pomieszczenia
        float poziomMocy = (wartoscZmierzona < wartoscZadana) ? 1.0f : 0.0f;
        grzejnik->ustawPoziomMocy(poziomMocy); //ustawienie mocy bezposrednio
    }
    bool czySkonfigurowany() const override
    {
        return pomieszczenie != nullptr && grzejnik != nullptr;
    }
};

#endif // REGULATORBB_HPP
