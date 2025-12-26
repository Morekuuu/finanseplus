#include <iostream>
#include "budzet.h"
#include <list>
#include <string>
#include <iomanip>
#include "struktury.h"

Budzet::Budzet(std::string n)
{
    nazwa = n;
}

// Metoda dodająca nową kwotę i miejsce do budżetu
void Budzet::dodajKonto(double kwota, std::string lokalizacja)
{
    konta.push_back(Konto(lokalizacja, kwota));
}

void Budzet::zmianaŚrodków()
{
    if (konta.empty())
    {
        std::cout << "Lista jest pusta, nie ma czego usuwac." << std::endl;
        return;
    }

    int a = 1;
    std::cout << "Dostępne Konta: " << std::endl;

    wyswietl();

    int numer;
    std::cout << "Podaj numer: ";
    std::cin >> numer;
    std::cin.ignore();



    if (numer > 0 && numer <= konta.size()) {
        auto it = konta.begin();
        std::advance(it, numer - 1);

        double zmiana;

        std::cout << "Znak '+' dodaje a znak '-' odejmuje" << std::endl;
        std::cout << "Podaj kwotę [PLN]: ";
        std::cin >> zmiana;
        it->saldoZmiana(zmiana);

        std::cout << "Do konta '" << it->nazwaZwrot() << "' zostalo "
            << ((zmiana<0) ? "odjęte: " : ("dodane: "))
            << zmiana << " PLN" << std::endl;
    } else {
        std::cout << "Nieprawidlowy numer." << std::endl;
    }
}

std::string Budzet::usunKonto()
{
    if (konta.empty()) {
        std::cout << "Lista jest pusta, nie ma czego usuwac." << std::endl;
        return "";
    }

    int a = 1;
    std::cout << "Dostępne Konta: " << std::endl;

    wyswietl();

    int numer;
    std::cout << "Podaj numer: ";
    std::cin >> numer;
    std::cin.ignore();

    if (numer > 0 && numer <= konta.size()) {
        auto it = konta.begin();
        std::advance(it, numer - 1);
        std::string lokalizacjaKasowana = it->nazwaZwrot();
        konta.erase(it);

        std::cout << "Konto '" << lokalizacjaKasowana << "' zostalo usunietę." << std::endl;
        return lokalizacjaKasowana;
    } else {
        std::cout << "Nieprawidlowy numer." << std::endl;
        return "";
    }
}

// Metoda obliczająca sumę w danym budżecie
double Budzet::sumaCalkowita() const
{
    double suma = 0;
    for (const auto& konto : konta)
    {
        suma += konto.saldoZwrot();
    }
    return suma;
}

// Wyświetlanie szczegółów budżetu
void Budzet::wyswietl() const
{
    std::cout << "=== Budzet: " << nazwa << " ===" << std::endl;
    if (konta.empty())
    {
        std::cout << "  (Brak srodkow)" << std::endl;
    }
    else
    {
        for (const auto& konto : konta)
        {
            std::cout << "  - " << konto.nazwaZwrot() << ": "
                 << std::fixed << std::setprecision(2) << konto.saldoZwrot() << " PLN" << std::endl;
        }
        std::cout << "  SUMA: " << std::fixed << std::setprecision(2) << sumaCalkowita() << " PLN" << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

void Budzet::wyswietl_dostepnosc() const
{
    std::cout << nazwa << std::endl;
    std::cout <<  "     środki budżetu: " << sumaCalkowita() << " PLN" << std::endl;
}

std::string Budzet::nazwaBudżetu()const
{
    return nazwa;
}

int Budzet::ileKont() const
{
    return konta.size();
}
