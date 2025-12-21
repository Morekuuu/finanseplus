#pragma once
#include <iostream>
#include <string>

class Konto
{
    public:
        Konto(std::string n, double s);
        std::string nazwaZwrot(); //metoda zwracająca nazwę
        double saldoZwrot(); //metoda zwracająca saldo

    private:
        std::string nazwa_;
        double saldo_;

};