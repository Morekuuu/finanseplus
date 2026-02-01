#pragma once
#include <string>
#include <iostream>

class Dlug
{
public:
    enum Typ { Zobowiazanie, Wierzytelnosc };

    Dlug(std::string k, double kw, Typ t, std::string o, std::string d);

    std::string ktoZwrot() const;
    double kwotaZwrot() const;
    Typ typZwrot() const;
    std::string opisZwrot() const;
    std::string dataZwrot() const;

    void splacCzesc(double ile); // Zmniejsza kwotę długu
    void wyswietl(int id) const; //Wyświetlanie

private:
    std::string kto_;
    double kwota_;
    Typ typ_;
    std::string opis_;
    std::string data_;
};
