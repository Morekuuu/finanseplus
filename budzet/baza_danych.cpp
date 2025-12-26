#include "baza_danych.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

const std::string NAZWA_PLIKU = "budzety.txt";
const std::string nazwa_pliku_logs = "historia.csv";

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

void odczytTransakcji()
{

}

void zapisTransackji(int zdarzenie, std::string rodzaj1, std::string rodzaj2)
{
    std::ofstream plik(nazwa_pliku_logs, std::ios::app);
    std::string wiadomosc;

    if (plik.is_open())
    {
        //Ustalanie wiadomości do zapisania
        switch (zdarzenie)
        {
        //Dodanie budżetu
        case 1:
            {
                wiadomosc = " Dodano nowy budżet " + rodzaj1;
                break;
            }
            //usnięto budżet
        case 2:
            {
                wiadomosc = " Usunięto budżet " + rodzaj1;
                break;
            }
        //Dodano nowe konto
        case 3:
            {
                wiadomosc = " Dodano nowe konto" + rodzaj2 + "do budżetu " + rodzaj1;
                break;
            }
        //Usuwanie konta
        case 4:
            {
                wiadomosc = "Usunięto konto " + rodzaj2 + " z budżetu " + rodzaj1;
                break;
            }
       //dodanie nowej nazwy konta
        case 5:
            {
                wiadomosc = " Dodano nową nazwę konta " + rodzaj2 + " do list kont";
                break;
            }
        //usuwanie nazwy konta
        case 6:
            {
                wiadomosc = " Usunięto nazwę konta " + rodzaj2 + " z list kont";
                break;
            }
        //odjęcie środków z konta <- nie zrobiłem
        case 7:
            {
                wiadomosc = " Odjęto środki z konta " + rodzaj2 + " z budżetu " + rodzaj1;
                break;
            }
        //Dodanie środków do konta <- nie zrobiłem
        case 8:
            {
                wiadomosc = " Dodanie środków do konta " + rodzaj2 + " w budżecie " + rodzaj1;
                break;
            }

        }



        //Zapis do pliku w formacie csv
        plik << pobierzDate() << ";" << wiadomosc << ";" << rodzaj1 << ";" << rodzaj2 << "\n";
        plik.close();

    } else {
        std::cout << "Nie znaleziona pliku historia.csv" << std::endl;
    }
}
//funkcja pobieranie daty
std::string pobierzDate()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);//konwersja na czas lokalny

    //formatowanie na tekst
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");

    return oss.str();
}
