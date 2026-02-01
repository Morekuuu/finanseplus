#pragma once
#include <string>

// Struktura reprezentująca pojedyncze miejsce przechowywania pieniędzy w danym budżecie
struct Konto {
    double kwota;
    std::string lokalizacja; // np. "Bank PKO", "Portfel"

    Konto(double k, std::string l) : kwota(k), lokalizacja(l) {}
};
