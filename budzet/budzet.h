#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include "struktury.h"

// Klasa reprezentująca jeden budżet tematyczny (np. "Wakacje")
class Budzet
{
    public:
        std::string nazwa;
        std::list<Konto> konta; // Lista kont wewnątrz tego budżetu

        Budzet(std::string n) : nazwa(n) {}

        // Metoda dodająca nową kwotę i miejsce do budżetu
        void dodajSrodki(double kwota, std::string lokalizacja) {
            konta.push_back(Konto(kwota, lokalizacja));
        }

        // Metoda obliczająca sumę w danym budżecie
        double sumaCalkowita() const {
            double suma = 0;
            for (const auto& konto : konta) {
                suma += konto.kwota;
            }
            return suma;
        }

        // Wyświetlanie szczegółów budżetu
        void wyswietl() const
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
                    std::cout << "  - " << konto.lokalizacja << ": "
                         << std::fixed << std::setprecision(2) << konto.kwota << " PLN" << std::endl;
                }
                std::cout << "  SUMA: " << std::fixed << std::setprecision(2) << sumaCalkowita() << " PLN" << std::endl;
            }
            std::cout << "-------------------------" << std::endl;
        }

        void wyswietl_dostepnosc() const
        {
            std::cout << nazwa << std::endl;
            std::cout <<  "     środki budżetu: " << sumaCalkowita() << " PLN" << std::endl;
        }
};
