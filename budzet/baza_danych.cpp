#include "baza_danych.h"
#include <iostream>
#include <fstream>
#include <string>

const std::string NAZWA_PLIKU = "budzety.txt";

void zapiszBaze(const std::list<Budzet>& lista, const std::list<std::string>& konta)
{
    std::ofstream plik(NAZWA_PLIKU);
    if (plik.is_open())
        {

        // Zapisywanie nazw kont
        plik << konta.size() << std::endl; // Ile jest nazw
        for (const auto& nazwa : konta)
        {
            plik << nazwa << std::endl;    // Sama nazwa
        }

        // Zapisywanie budżetów
        plik << lista.size() << std::endl;
        for (const auto& budzet : lista)
        {
            plik << budzet.nazwaBudżetu() << std::endl;
            plik << budzet.ileKont() << std::endl;

            for (const auto& konto : budzet.konta)
            {
                plik << konto.nazwaZwrot() << std::endl;
                plik << konto.saldoZwrot() << std::endl;
            }
        }
        plik.close();
        std::cout << "[INFO] Dane zostaly zapisane do pliku " << NAZWA_PLIKU << std::endl;
    } else {
        std::cout << "[BLAD] Nie udalo sie otworzyc pliku do zapisu!" << std::endl;
    }
}

void wczytajBaze(std::list<Budzet>& lista, std::list<std::string>& konta)
{
    std::ifstream plik(NAZWA_PLIKU);
    if (plik.is_open())
    {
        lista.clear();
        konta.clear();

        // Wczytanie listy nazw kont
        int iloscNazw = 0;
        if (plik >> iloscNazw)
            {
            plik.ignore();

            for (int i = 0; i < iloscNazw; i++) {
                std::string nazwa;
                getline(plik, nazwa);
                konta.push_back(nazwa);
            }
        }

        // Wczytanie listy budżetów
        int iloscBudzetow;
        plik >> iloscBudzetow;
        plik.ignore();

        for (int i = 0; i < iloscBudzetow; i++)
        {
            std::string nazwaBudzetu;
            getline(plik, nazwaBudzetu);

            Budzet nowyBudzet(nazwaBudzetu);

            int iloscKont;
            plik >> iloscKont;
            plik.ignore();

            for (int j = 0; j < iloscKont; j++)
            {
                std::string lokalizacja;
                double kwota;

                getline(plik, lokalizacja);
                plik >> kwota;
                plik.ignore(); // Ignorujemy nową linię po kwocie

                nowyBudzet.dodajKonto(kwota, lokalizacja);
            }
            lista.push_back(nowyBudzet);
        }
        plik.close();
        std::cout << "[INFO] Wczytano dane z pliku (" << lista.size() << " budzetow)." << std::endl;
    }
    else
    {
        std::cout << "[INFO] Brak pliku zapisu lub pierwszy start programu." << std::endl;
    }
}
