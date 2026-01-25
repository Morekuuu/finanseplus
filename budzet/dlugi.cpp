#include "dlugi.h"

Dlug::Dlug(std::string k, double kw, Typ t, std::string o, std::string d)
    : kto_(k), kwota_(kw), typ_(t), opis_(o), data_(d) 
{
}

//Gettery
std::string Dlug::ktoZwrot() const { return kto_; }
double Dlug::kwotaZwrot() const { return kwota_; }
Dlug::Typ Dlug::typZwrot() const { return typ_; }
std::string Dlug::opisZwrot() const { return opis_; }
std::string Dlug::dataZwrot() const { return data_; }

// Zmniejszanie długu
void Dlug::splacCzesc(double ile)
{
    kwota_ -= ile;
    if (kwota_ < 0) kwota_ = 0;
}

// Wyświetlanie
void Dlug::wyswietl(int id) const
{
    std::string rodzajStr = (typ_ == Zobowiazanie) ? "Musze oddac dla: " : "Wisi mi kase: ";
    
    std::cout << id << ". " << rodzajStr << kto_ 
              << " | Kwota: " << kwota_ << " PLN"
              << " | Opis: " << opis_ << " (" << data_ << ")" << std::endl;
}
