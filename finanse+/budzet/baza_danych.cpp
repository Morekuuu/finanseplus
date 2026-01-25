#include "baza_danych.h"
#include "dlugi.h"
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
        plik << konta.size() << std::endl;
        for (const auto& nazwa : konta)
        {
            plik << nazwa << std::endl;
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
                plik << (int)konto.rodzajZwrot() << std::endl;
                plik << konto.oprocentowanieZwrot() << std::endl;
                plik << konto.cyklZwrot() << std::endl;
                plik << konto.dataZwrot() << std::endl;
                plik << konto.czasTrwaniaZwrot() << std::endl;
                plik << konto.celZwrot() << std::endl;
            }
        }
        plik.close();
        std::cout << "[INFO] Dane zostaly zapisane do pliku " << NAZWA_PLIKU << std::endl;
    } else {
        std::cout << "[BLAD] Nie udalo sie otworzyc pliku do zapisu!" << std::endl;
    }
}

void wczytajBaze(std::list<Budzet>& lista, std::list<std::string>& nazwyKont)
{
    std::ifstream plik(NAZWA_PLIKU);
    if (plik.is_open())
    {
        lista.clear();
        nazwyKont.clear();

        // 1. Wczytanie nazw kont
        int iloscNazw = 0;
        if (plik >> iloscNazw) {
            plik.ignore();
            for (int i = 0; i < iloscNazw; i++) {
                std::string nazwa;
                std::getline(plik, nazwa);
                nazwyKont.push_back(nazwa);
            }
        }

        // 2. wczytywanie budżetów
        int iloscBudzetow;
        plik >> iloscBudzetow;
        plik.ignore();

        for (int i = 0; i < iloscBudzetow; i++)
        {
            std::string nazwaBudzetu;
            std::getline(plik, nazwaBudzetu);

            Budzet nowyBudzet(nazwaBudzetu);

            int iloscKontWBudzecie;
            plik >> iloscKontWBudzecie;
            plik.ignore();

            for (int j = 0; j < iloscKontWBudzecie; j++)
            {
                //Zmienne tymczasowe na wszystkie pola
                std::string lokalizacja;
                double kwota;
                int rodzajInt;
                double oprocentowanie;
                double cykl;
                long long data;
                long long trwanie;
                std::string cel;

                //Wczytywanie pól
                std::getline(plik, lokalizacja);
                plik >> kwota;
                plik >> rodzajInt;
                plik >> oprocentowanie;
                plik >> cykl;
                plik >> data;
                plik >> trwanie;
                plik.ignore();
                std::getline(plik, cel);

                // tworzenie obiektu Kontot
                Konto k(lokalizacja, kwota, (Konto::rodzaj)rodzajInt, oprocentowanie, cykl, data, trwanie, cel);

                //Aktualizacja odsetek
                k.aktualizujStan();

                // Dodajemy do listy w budżecie
                nowyBudzet.konta.push_back(k);
            }
            lista.push_back(nowyBudzet);
        }
        plik.close();
        std::cout << "[INFO] Wczytano dane." << std::endl;
    }
    else
    {
        std::cout << "[INFO] Brak pliku lub pierwszy start." << std::endl;
    }
}

void odczytTransakcji()
{
//Ostatecznie sobie odpuszczam w tym miejscu, odczyt od razu w gui
}

void zapisTransackji(int zdarzenie, std::string rodzaj1, std::string rodzaj2)
{
    std::ofstream plik(nazwa_pliku_logs, std::ios::app);
    std::string wiadomosc;

    if (plik.is_open())
    {
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

    }
    else
    {
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

void zapiszDlugi(const std::list<Dlug>& lista)
{
    std::ofstream plik("dlugi.txt");
    if (plik.is_open())
    {
        plik << lista.size() << std::endl;
        for (const auto& d : lista)
        {
            plik << d.ktoZwrot() << std::endl;
            plik << d.kwotaZwrot() << std::endl;
            plik << (int)d.typZwrot() << std::endl;
            plik << d.dataZwrot() << std::endl;
            plik << d.opisZwrot() << std::endl;
        }
        plik.close();
    }
}

void wczytajDlugi(std::list<Dlug>& lista)
{
    std::ifstream plik("dlugi.txt");
    lista.clear();
    if (plik.is_open())
    {
        int ilosc;
        plik >> ilosc;
        plik.ignore();

        for (int i = 0; i < ilosc; i++)
        {
            std::string kto, opis, data;
            double kwota;
            int typInt;

            std::getline(plik, kto);
            plik >> kwota;
            plik >> typInt;
            plik.ignore();
            std::getline(plik, data);
            std::getline(plik, opis);

            // Konstruktor klasy Dlug
            lista.push_back(Dlug(kto, kwota, (Dlug::Typ)typInt, opis, data));
        }
        plik.close();
        std::cout << "[INFO] Wczytano " << lista.size() << " dlugow." << std::endl;
    }
}
