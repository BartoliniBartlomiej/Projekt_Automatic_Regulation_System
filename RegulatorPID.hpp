//// RegulatorPID.hpp
//#ifndef REGULATORPID_HPP
//#define REGULATORPID_HPP
//
//#include "Regulator.hpp"
//#include <algorithm>
//#include <iostream>
//
//class RegulatorPID : public Regulator 
//{
//public:
//    RegulatorPID(float Kp, float Ki, float Kd) : Kp(Kp), Ki(Ki), Kd(Kd), e_calka(0.0f), e_poprzednia(0.0f) {}
//
//    float steruj(float wartoscZadana, float wartoscZmierzona, float dt) override 
//    {
//        //std::cout<<"METODA STERUJ\n";
//        float e = wartoscZadana - wartoscZmierzona; //e to roznica miedzy wartoscia docelową a aktualnie zmierzona
//        e_calka += e * dt;
//        float e_roznica = (e - e_poprzednia) / dt;
//        e_poprzednia = e;
//
//        float u = Kp * e + Ki * e_calka + Kd * e_roznica;
//        return std::clamp(u, 0.0f, 1.0f); //ograniczenie mocy do przedziału 0-1
//    }
//
//private:
//    float Kp, Ki, Kd;
//    float e_calka, e_poprzednia;
//};
//
//#endif // REGULATORPID_HPP

#ifndef REGULATORPID_HPP
#define REGULATORPID_HPP

#include "Regulator.hpp"
#include <algorithm>

class RegulatorPID : public Regulator
{
public:
    RegulatorPID(float Kp, float Ki, float Kd) 
    : Kp(Kp)
    , Ki(Ki), Kd(Kd)
    , e_calka(0.0f)
    , e_poprzednia(0.0f)
    {}

    void steruj(float wartoscZadana, float dt) override
    {
        if (!czySkonfigurowany())
        {
            throw std::runtime_error("RegulatorBB nie jest skonfigurowany.");
        }
        if (dt == 0.0f)
        {
            throw "dt nie może być zerem.";
        }
        
        float wartoscZmierzona = pomieszczenie->getTemperatura(); //dostep do pomieszczenia
        float e = wartoscZadana - wartoscZmierzona;
        e_calka += e * dt;
        float e_roznica = (e - e_poprzednia) / dt;
        e_poprzednia = e;

        float u = Kp * e + Ki * e_calka + Kd * e_roznica;
        float poziomMocy = std::clamp(u, 0.0f, 1.0f);
        grzejnik->ustawPoziomMocy(poziomMocy);
    }
    
    bool czySkonfigurowany() const override
    {
        return pomieszczenie != nullptr && grzejnik != nullptr;
    }

private:
    float Kp, Ki, Kd;
    float e_calka, e_poprzednia;
};

#endif // REGULATORPID_HPP
