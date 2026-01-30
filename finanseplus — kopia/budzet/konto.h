#pragma once
#include <string>
#include <ctime>

// Struktura pomocnicza - określa cel odsetek
struct WynikOdsetek
{
    double kwota;
    std::string celTransferu; // Jeśli puste -> dodaj do tego samego konta
};

class Konto
{
public:
    enum rodzaj { basic, saving, deposit, bonds, credit };

    Konto(std::string n, double s, rodzaj r = basic,
          double opr = 0.0, double cykl = 0.0,
          long long data = 0,
          long long czasTrwania = 0, std::string cel = "");

    // Gettery
    std::string nazwaZwrot() const;
    double saldoZwrot() const;
    rodzaj rodzajZwrot() const;
    double oprocentowanieZwrot() const;
    double cyklZwrot() const;
    long long dataZwrot() const;
    long long czasTrwaniaZwrot() const;
    std::string celZwrot() const;

    void saldoZmiana(double zmiana);
    WynikOdsetek aktualizujStan();

private:
    std::string nazwa_;
    double saldo_;
    rodzaj rodzaj_;

    //Ogólne pola oprocentowań
    double oprocentowanie_;
    double okresCykluZmian_;
    long long ostatniaAktualizacja_;

    //Obligacje
    long long okresTrwania_; // Czas trwania obligacji
    std::string celTransferu_; // miejsce wypłacania odsetek
    long long dataRozpoczecia_; // rozpoczęcie obligacji
};
