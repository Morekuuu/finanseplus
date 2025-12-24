#include "konto.h"


Konto::Konto(std::string n, double s)
{
    nazwa_ = n;
    saldo_ = s;
}

std::string Konto::nazwaZwrot() const
{
    return nazwa_;
}

void Konto::saldoZmiana(double zmiana)
{
    saldo_ += zmiana;
}

double Konto::saldoZwrot() const
{
    return saldo_;
}
