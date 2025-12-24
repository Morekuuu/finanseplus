#pragma once
#include <iostream>
#include <string>

class Konto
{
    public:
        Konto(std::string n, double s);
        std::string nazwaZwrot() const; //metoda zwracająca nazwę
        double saldoZwrot() const; //metoda zwracająca saldo

        void saldoZmiana(double zmiana); //Metoda zmieniająca saldo

    private:
        std::string nazwa_;
        double saldo_;


};
