#include "baza_danych.h"
#include <iostream>
#include <fstream>
#include <string>

const std::string NAZWA_PLIKU = "budzety.txt";

void zapiszBaze(const std::list<Budzet>& lista)
{
    std::ofstream plik(NAZWA_PLIKU);
    if (plik.is_open()) {
        // Najpierw zapisujemy ile mamy budżetów
        plik << lista.size() << std::endl;

        for (const auto& budzet : lista) {
            // Zapisujemy nazwę budżetu
            plik << budzet.nazwa << std::endl;
            // Zapisujemy ile kont ma ten budżet
            plik << budzet.konta.size() << std::endl;

            for (const auto& konto : budzet.konta) {
                // Zapisujemy dane konta: lokalizacja i kwota
                plik << konto.lokalizacja << std::endl;
                plik << konto.kwota << std::endl;
            }
        }
        plik.close();
        std::cout << "[INFO] Dane zostaly zapisane do pliku " << NAZWA_PLIKU << std::endl;
    } else {
        std::cout << "[BLAD] Nie udalo sie otworzyc pliku do zapisu!" << std::endl;
    }
}

void wczytajBaze(std::list<Budzet>& lista)
{
    std::ifstream plik(NAZWA_PLIKU);
    if (plik.is_open()) {
        int iloscBudzetow;
        plik >> iloscBudzetow;
        plik.ignore(); // Ignorujemy znak nowej linii po wczytaniu liczby

        for (int i = 0; i < iloscBudzetow; i++) {
            std::string nazwaBudzetu;
            getline(plik, nazwaBudzetu); // Wczytujemy nazwę budżetu (może mieć spacje)

            Budzet nowyBudzet(nazwaBudzetu);

            int iloscKont;
            plik >> iloscKont;
            plik.ignore(); // Znów ignorujemy nową linię po liczbie

            for (int j = 0; j < iloscKont; j++) {
                std::string lokalizacja;
                double kwota;

                getline(plik, lokalizacja);
                plik >> kwota;
                plik.ignore(); // Ignorujemy nową linię po kwocie

                nowyBudzet.dodajSrodki(kwota, lokalizacja);
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