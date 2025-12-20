#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <fstream>
#include "budzet.h"
#include "baza_danych.h"
#include <windows.h>

using namespace std;

const string NAZWA_PLIKU = "budzety.txt";

// Funkcja pomocnicza do pobierania linii tekstu (radzi sobie ze spacjami)
string wczytajLinie()
{
    string tekst;
    getline(cin, tekst);
    return tekst;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // Główna lista przechowywująca wszystkie budżety
    list<Budzet> listaBudzetow;

    wczytajBaze(listaBudzetow);


    int wybor;
    do
    {
        cout << "\n--- MENADZER BUDZETOW ---" << endl;
        cout << "1. Dodaj nowy budżet tematyczny" << endl;
        cout << "2. Dodaj środki do istniejacego budżetu" << endl;
        cout << "3. Wyswietl wszystkie budżety" << endl;
        cout << "4. odejmij środki" << endl;
        cout << "5. Usuń środki" << endl;
        cout << "6. Usuń budżet" << endl;
        cout << "0. Wyjście" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cin.ignore();

        switch (wybor)
        {
        case 1:
        {

            cout << "Podaj nazwe nowego budzetu (np. Wakacje): ";
            string nazwa = wczytajLinie();
            listaBudzetow.push_back(Budzet(nazwa));
            cout << "Budzet '" << nazwa << "' zostal utworzony." << endl;
            break;
        }
        case 2:
        {
            if (listaBudzetow.empty())
            {
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

            if (numer > 0 && numer <= listaBudzetow.size())
            {
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
            } else {cout << "Nieprawidlowy numer." << endl;}
            break;
        }
        case 3:
            {
                if (listaBudzetow.empty())
                {
                    cout << "Lista budzetow jest pusta." << endl;
                }
                else
                {
                    cout << "\nWSZYSTKIE TWOJE BUDZETY:" << endl;
                    for (const auto& b : listaBudzetow)
                        {b.wyswietl();}
                }
            break;
            }
        case 4:
            {
                cout << "4. odejmij środki";
                break;
            }
        case 5:
            {
                cout << "6. Usuń środki";

                break;
            }
        case 6:
            {
                if (listaBudzetow.empty()) {
                    cout << "Lista jest pusta, nie ma czego usuwac." << endl;
                    break;
                }

                int a = 1;
                cout << "Dostępne budżety: " << endl;
                for (const auto& b : listaBudzetow)
                {
                    cout << a << ". ";
                    b.wyswietl_dostepnosc();
                    a++;
                }

                int numer;
                cout << "Podaj numer: ";
                cin >> numer;
                cin.ignore();

                if (numer > 0 && numer <= listaBudzetow.size()) {
                    auto it = listaBudzetow.begin();
                    advance(it, numer - 1);
                    string Nazwakasowana = it->nazwa;
                    listaBudzetow.erase(it);

                    cout << "Budzet '" << Nazwakasowana << "' zostal usuniety." << endl;
                } else {
                    cout << "Nieprawidlowy numer." << endl;
                }
                break;
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
