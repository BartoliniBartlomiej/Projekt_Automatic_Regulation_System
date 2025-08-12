#include <iostream>
#include "Pomieszczenie.hpp"
#include "Symulacja.hpp"
#include "Grzejnik.hpp"
#include "RegulatorBB.hpp"
#include "RegulatorPID.hpp"

int main()
{
    float r, s, t;
    int i;
    
    //dlugosc kroku, ilosc krokow i temperatura
    
    // Domyślne pomieszczenie
    Pomieszczenie pomieszczenie(5.0f, 4.0f, 2.5f);

    // Domyślna moc grzejnika
    Grzejnik grzejnik(3000.0f);

    Symulacja symulacja(pomieszczenie, grzejnik);

    // Domyślna wartość zadana temperatury
    //symulacja.ustawWartoscZadana(25.0f);
    
    while (true)
    {
        std::cout << "Wybierz regulator: \n";
        std::cout << "1. BB. \n";
        std::cout << "2. PID. \n";
        std::cin >> r;
        
     
        if (r == 1)
        {
            RegulatorBB regulatorBB;
            regulatorBB.ustawPomieszczenie(&pomieszczenie);
            regulatorBB.ustawGrzejnik(&grzejnik);
            symulacja.ustawRegulator(&regulatorBB);
            break;
        }
        if (r == 2)
        {
            RegulatorPID regulatorPID(4.0f, 0.02f, 0.1f);
            regulatorPID.ustawPomieszczenie(&pomieszczenie);
            regulatorPID.ustawGrzejnik(&grzejnik);
            symulacja.ustawRegulator(&regulatorPID);
            break;
        }
        if (std::cin.fail() || (r != 1 && r != 2))
        {
            std::cin.clear(); // czysci flagę błędu
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidłowy wybór. Proszę wybrać 1 lub 2.\n";
        }
    }

    s = symulacja.ustawDt();
    i = symulacja.ustawLiczbaKroków();
    t = symulacja.ustawTempDoc();
    //symulacja.przebieg(i, s);
    
    symulacja.ustawWartoscZadana(t);
    symulacja.przebieg(i, s);
    symulacja.zapis("/Users/bartek/Studia/Programowanie C++/projekt3_UAR/projekt3_UAR/symulacja.csv");

    return 0;
}

