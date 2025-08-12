#include "Symulacja.hpp"
#include <iostream>


void Symulacja::iteracja(float dt)
{

    regulator->steruj(wartoscZadana, dt);
    pomieszczenie.dodajCieplo(grzejnik.obliczCieplo());
    pomieszczenie.aktualizuj(dt);
    czas += dt;

    float wartoscZmierzona = pomieszczenie.getTemperatura();
    temperatury.push_back(wartoscZmierzona);
    czasy.push_back(czas);
    moce.push_back(grzejnik.obliczCieplo());

    std::cout << "Aktualna temperatura: " << wartoscZmierzona << std::endl;
    std::cout << "Poziom mocy: " << grzejnik.obliczCieplo() << std::endl;
}

void Symulacja::przebieg(int liczbaIteracji, float dt) 
{
    for (int i = 0; i < liczbaIteracji; ++i)
    {
        iteracja(dt);
    }
}

void Symulacja::zapis(const std::string& nazwaPliku) const
{
    std::ofstream plik(nazwaPliku);
    plik << "Czas[s],Temperatura[degC],Moc[W], Poziom Mocy[%]\n";
    
    for (size_t i = 0; i < czasy.size(); ++i) 
    {
        float poziomMocy = 100*moce[i] / grzejnik.getMocNominalna();  // procentowy poziom aktualnej mocy
        plik << czasy[i] << "," << temperatury[i] << "," << moce[i] << "," << poziomMocy << "\n";
    }
}

float Symulacja::ustawDt()
{
    float s;
    std::cout<<"Długość kroku [s]: ";
    std::cin >> s;
    return s;
}

int Symulacja::ustawLiczbaKroków()
{
    int k;
    std::cout<<"Ilość kroków: ";
    std::cin >> k;
    return k;
}
float Symulacja::ustawTempDoc()
{
    float t;
    std::cout << "Ustaw wartość zadaną temp: ";
    std::cin >> t;
    return t;
}
