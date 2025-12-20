#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <fstream>
#include "budzet.h"
#include "baza_danych.h"

using namespace std;

const string NAZWA_PLIKU = "budzety.txt";

// Funkcja pomocnicza do pobierania linii tekstu (radzi sobie ze spacjami)
string wczytajLinie() {
    string tekst;
    getline(cin, tekst);
    return tekst;
}

int main() {
    // Główna lista przechowywująca wszystkie budżety
    list<Budzet> listaBudzetow;

    wczytajBaze(listaBudzetow);


    int wybor;

    do {
        cout << "\n--- MENADZER BUDZETOW ---" << endl;
        cout << "1. Dodaj nowy budzet tematyczny" << endl;
        cout << "2. Dodaj srodki do istniejacego budzetu" << endl;
        cout << "3. Wyswietl wszystkie budzety" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cin.ignore(); // Czyszczenie bufora po cin >> wybor

        switch (wybor) {
        case 1: {
            cout << "Podaj nazwe nowego budzetu (np. Wakacje): ";
            string nazwa = wczytajLinie();
            listaBudzetow.push_back(Budzet(nazwa));
            cout << "Budzet '" << nazwa << "' zostal utworzony." << endl;
            break;
        }
        case 2: {
            if (listaBudzetow.empty()) {
                cout << "Najpierw utworz jakis budzet!" << endl;
                break;
            }

            cout << "Wybierz budzet do edycji:" << endl;
            int i = 1;
            // Wyświetlamy listę budżetów z numerami
            for (const auto& b : listaBudzetow) {
                cout << i << ". " << b.nazwa << endl;
                i++;
            }

            int numer;
            cout << "Podaj numer: ";
            cin >> numer;
            cin.ignore();

            if (numer > 0 && numer <= listaBudzetow.size()) {
                // Znajdowanie elementu w liście (listy nie mają dostępu przez [], więc używamy iteratora)
                auto it = listaBudzetow.begin();
                advance(it, numer - 1); // Przesuwamy iterator na wybraną pozycję

                cout << "Podaj kwote: ";
                double kwota;
                cin >> kwota;
                cin.ignore();

                cout << "Podaj miejsce przechowywania (np. PKO, Gotowka): ";
                string miejsce = wczytajLinie();

                it->dodajSrodki(kwota, miejsce);
                cout << "Dodano srodki." << endl;
            } else {
                cout << "Nieprawidlowy numer." << endl;
            }
            break;
        }
        case 3: {
            if (listaBudzetow.empty()) {
                cout << "Lista budzetow jest pusta." << endl;
            } else {
                cout << "\nWSZYSTKIE TWOJE BUDZETY:" << endl;
                for (const auto& b : listaBudzetow) {
                    b.wyswietl();
                }
            }
            break;
        }
        case 0:
            zapiszBaze(listaBudzetow);
            cout << "Konczenie programu..." << endl;

            break;
        default:
            cout << "Nieznana opcja." << endl;
        }

    } while (wybor != 0);

    return 0;
}
