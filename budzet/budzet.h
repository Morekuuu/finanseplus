#pragma once
#include <iostream>
#include <list>
#include <string>
#include <iomanip>
//#include "struktury.h"
#include "konto.h"

class Budzet
{
    public:
        Budzet(std::string n);

        // Metoda dodająca nową kwotę i miejsce do budżetu
        void dodajKonto(double kwota, std::string lokalizacja);

        // Dodaje środki do wybranego konta
        void zmianaŚrodków();

        // Metoda usuwająca konto w budżecie wraz z środkami
        std::string usunKonto();

        // Metoda obliczająca sumę w danym budżecie
        double sumaCalkowita() const;

        // Wyświetlanie szczegółów budżetu
        void wyswietl() const;

        // Metoda na wyświetlenie nazwy oraz sumy środków budżetu
        void wyswietl_dostepnosc() const;

        // Metoda zwracająca nazwę
        std::string nazwaBudżetu()const;

        //Metoda dodająca kwoty z obligacji
        void przeliczWszystkieKonta();

        // Metoda zwracająca ilosć dopisanych kont do budżetu
        int ileKont() const;

        std::list<Konto> konta; // Lista kont wewnątrz tego budżetu

    private:
        std::string nazwa;

};
