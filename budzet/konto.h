#pragma once
#include <iostream>
#include <string>

class Konto
{
    public:
        Konto(std::string n, double s);
        enum rodzaj {basic, saving, deposit, bonds, credit}; //definiowanie typów konta

        std::string nazwaZwrot() const; //metoda zwracająca nazwę
        double saldoZwrot() const; //metoda zwracająca saldo

        void saldoZmiana(double zmiana); //Metoda zmieniająca saldo

    private:
        std::string nazwa_; //zmienna nazwy konta
        double saldo_; //zmienna salda konta
        rodzaj rodzaj_; //zmienna rodzaju konta
        double oprocentowanie_;
        double okresCykluZmian_;
        double okresTrwania_;

};
