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
        Budzet(std::string n);

        // Metoda dodająca nową kwotę i miejsce do budżetu
        void dodajKonto(double kwota, std::string lokalizacja);

        // Dodaje środki do wybranego konta
        void zmianaŚrodków();

        // Metoda usuwająca konto w budżecie wraz z środkami
        void usunKonto();

        // Metoda obliczająca sumę w danym budżecie
        double sumaCalkowita() const;

        // Wyświetlanie szczegółów budżetu
        void wyswietl() const;

        // Metoda na wyświetlenie nazwy oraz sumy środków budżetu
        void wyswietl_dostepnosc() const;

        std::string nazwaBudżetu()const;

        int ileKont() const;

        std::list<Konto> konta; // Lista kont wewnątrz tego budżetu

    private:
        std::string nazwa;

};
