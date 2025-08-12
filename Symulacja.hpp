#ifndef SYMULACJA_HPP
#define SYMULACJA_HPP

#include "Pomieszczenie.hpp"
#include "Grzejnik.hpp"
#include "Regulator.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>

class Symulacja {
public:
    Symulacja(Pomieszczenie& pomieszczenie, Grzejnik& grzejnik)
    : pomieszczenie(pomieszczenie)
    , grzejnik(grzejnik)
    , czas(0.0f)
    {}
    
    void iteracja(float dt);
    void przebieg(int liczbaIteracji, float dt);
    void zapis(const std::string& nazwaPliku) const;
    void ustawRegulator(Regulator* regulator)
    {
        this->regulator = regulator;
    }
    void ustawWartoscZadana(float wartoscZadana) 
    {
        this->wartoscZadana = wartoscZadana;
    }
    ~Symulacja() = default;
    
    float ustawDt();
    int ustawLiczbaKroków();
    float ustawTempDoc();
    
    
    
private:
    Pomieszczenie& pomieszczenie;
    Grzejnik& grzejnik;
    float czas;
    std::vector<float> czasy;
    std::vector<float> temperatury;
    std::vector<float> moce;
    Regulator* regulator;
    float wartoscZadana;
};

#endif // SYMULACJA_HPP
