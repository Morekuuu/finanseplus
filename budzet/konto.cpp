#include "konto.h"


Konto::Konto(std::string n, double s)
{
    nazwa_ = n;
    saldo_ = s;
}

std::string Konto::nazwaZwrot()
{
    return nazwa_;
}

double Konto::saldoZwrot()
{
    return saldo_;
}
