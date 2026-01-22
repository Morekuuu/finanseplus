#include "konto.h"
#include <cmath>
#include <iostream>

Konto::Konto(std::string n, double s, rodzaj r, double opr, double cykl, long long data, long long trwanie, std::string cel)
    : nazwa_(n), saldo_(s), rodzaj_(r), oprocentowanie_(opr), okresCykluZmian_(cykl), okresTrwania_(trwanie), celTransferu_(cel)
{
    if (data == 0) {
        ostatniaAktualizacja_ = std::time(nullptr);
        dataRozpoczecia_ = ostatniaAktualizacja_;
    }
    else
    {
        ostatniaAktualizacja_ = data;
        dataRozpoczecia_ = data;
    }
}

//Gettery

std::string Konto::nazwaZwrot() const {return nazwa_;}

double Konto::saldoZwrot() const {return saldo_;}

Konto::rodzaj Konto::rodzajZwrot() const {return rodzaj_;}

double Konto::oprocentowanieZwrot() const {return oprocentowanie_;}

double Konto::cyklZwrot() const {return okresCykluZmian_;}

long long Konto::dataZwrot() const {return ostatniaAktualizacja_;}

long long Konto::czasTrwaniaZwrot() const {return okresTrwania_;}

std::string Konto::celZwrot() const {return celTransferu_;}


//metody
void Konto::saldoZmiana(double zmiana) {saldo_ += zmiana;}

WynikOdsetek Konto::aktualizujStan()
{
    WynikOdsetek wynik = {0.0, ""};
    if (rodzaj_ != saving && rodzaj_ != bonds) return wynik;
    if (okresCykluZmian_ <= 0) return wynik;

    time_t teraz = std::time(nullptr);

    //Operacje dla obligacji
    if (rodzaj_ == bonds)
    {
        long long wiekObligacji = (long long)teraz - dataRozpoczecia_;

        if (wiekObligacji > okresTrwania_ && okresTrwania_ > 0)
        {
            // Obligacja wygasła
            return wynik;
        }

        double roznicaCzasu = std::difftime(teraz, (time_t)ostatniaAktualizacja_);
        int ileCykli = (int)(roznicaCzasu / okresCykluZmian_);

        if (ileCykli > 0)
        {
            double zysk = saldo_ * oprocentowanie_ * ileCykli;

            wynik.kwota = zysk;
            wynik.celTransferu = celTransferu_;

            ostatniaAktualizacja_ += (long long)(ileCykli * okresCykluZmian_);
        }
    }
    //Logika dla oszczędnościowego
    else if (rodzaj_ == saving)
    {
        double roznicaCzasu = std::difftime(teraz, (time_t)ostatniaAktualizacja_);
        int ileCykli = (int)(roznicaCzasu / okresCykluZmian_);

        if (ileCykli > 0)
        {
            // Procent składany
            double mnoznik = std::pow(1.0 + oprocentowanie_, ileCykli);
            double stareSaldo = saldo_;
            saldo_ = saldo_ * mnoznik;

            ostatniaAktualizacja_ += (long long)(ileCykli * okresCykluZmian_);

            wynik.kwota = saldo_ - stareSaldo;
        }
    }

    return wynik;
}
