/* Lista To Do
 *
 *  1. Blokada usuwania nazwy konta jeśli istnieje w użyciu
 *  2. Dodanie potwierdzenia przy usuwaniu budżetu oraz konta z budżetu
 *  4. Dodanie historii transakcji
 *  5. GUI
 *  6. Dodanie przesyłu środków z kaucji
 *  7. Dodawanie spersjonalizowanych produktów inwestycyjnych
 *  8.
 *
 *  Zrobione:
 *  3. Dodanie raportu
 *
 */


#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <fstream>
#include <windows.h>

#include "budzet.h"
#include "baza_danych.h"

using namespace std;

// Funkcja do pobierania linii tekstu (radzi sobie ze spacjami)
string wczytajLinie()
{
    string tekst;
    getline(cin, tekst);
    return tekst;
}

// Funkcja do wyświetlania listy budżetów
void Budzety(std::list<Budzet>& lista)
{
    int i = 1;
    for (const auto& b : lista) {
        cout << i << ". " << b.nazwaBudżetu() << endl;
        i++;
    }
}

//Funkcja do modyfikowania listy kont
void modListaKont(std::list<std::string>& lista)
{
    int i;
    cout << "Co chcesz zrobić" << endl;
    cout << "1. Dodać konto" << endl;
    cout << "2. Usunąć konto" << endl;
    cout << "3. Wyświetl konta" << endl;
    cin >> i;
    switch (i)
    {
        case 1:
        {
                cout << "Podaj nazwe nowego konta: ";
                string nazwa;
                cin >> nazwa;
                lista.push_back(nazwa);
                cout << "Konto " << nazwa << " dodane"<< endl;
                zapisTransackji(1, nazwa, " ");
                break;
        } //Dodawanie bużetu
        case 2:
        {
                if (lista.empty()) {std::cout << "Lista kont jest pusta." << std::endl;}
                else
                {
                    int idx = 1;
                    std::cout << "Dostepne konta:" << std::endl;
                    for (const auto& nazwa : lista)
                    {
                        std::cout << idx << ". " << nazwa << std::endl;
                        idx++;
                    }
                    int idxDelete;
                    cout << "Podaj numer do usunięcia: ";
                    cin >> idxDelete;
                    idx = 1;
                    for (const auto& nazwa : lista)
                    {
                        if (idx == idxDelete)
                        {
                            lista.remove(nazwa);
                            std::cout << "Usunięto: " << idx << ". " << nazwa << std::endl;
                        }
                        else {cout << "Nieprawidłowy numer";}
                        idx++;
                    }


                }
                break;
        } //Usuwanie konta z budżetu
        case 3:
        {
                if (lista.empty()) {std::cout << "Lista kont jest pusta." << std::endl;}
                else
                {
                    int idx = 1;
                    std::cout << "Dostepne konta:" << std::endl;
                    for (const auto& nazwa : lista)
                    {
                        std::cout << idx << ". " << nazwa << std::endl;
                        idx++;
                    }
                }
                break;

        }
        default:
        {
            cout << "Nieprawidłowy numer";
        }
    }
}

//Sprawdza czy podana nazwa konta istnieje w liście nazw kont
bool nazwaKontaPoprawna(std::string nazwa, const std::list<std::string>& dozwoloneNazwy)
{
    for (const std::string& nazwaZListy : dozwoloneNazwy)
    {
        if (nazwaZListy == nazwa) {return true;}
    }
    return false;
}

//Generuje raport kont
void raport(std::list<Budzet>& Budzety, std::list<std::string>& Konta)
{
    std::cout << "\n--- RAPORT ZBIORCZY ---" << std::endl;
    for (const std::string& szukanaNazwa : Konta)
    {
        double sumaDlaKategorii = 0.0;
        for (Budzet& obecnyBudzet : Budzety)
            {
            for (Konto& konto : obecnyBudzet.konta)
            {
                if (konto.nazwaZwrot() == szukanaNazwa)
                {
                    sumaDlaKategorii += konto.saldoZwrot();
                }
            }
        }
        std::cout << "Konto:  " << szukanaNazwa << ": " << sumaDlaKategorii << " zl" << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // Główna lista przechowywująca wszystkie budżety
    list<Budzet> listaBudzetow;

    // Lista do przechowywania dozwolonych nazw kont
    std::list<std::string> nazwyKont;

    wczytajBaze(listaBudzetow, nazwyKont);


    int wybor;
    do
    {
        cout << "\n--- MENADZER BUDZETOW ---" << endl;
        cout << "1. Dodaj nowy budżet" << endl;
        cout << "2. Dodaj konto do budżetu" << endl;
        cout << "3. Wyswietl wszystkie budżety" << endl;
        cout << "4. Zmiana środków" << endl;
        cout << "5. Usuń środki" << endl;
        cout << "6. Usuń budżet" << endl;
        cout << "7. Zmień dostępne konta" << endl;
        cout << "8. Raport kont" << endl;
        cout << "0. Wyjście" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cin.ignore();

        switch (wybor)
        {
        case 1: // dodanie nowego budżetu
        {

            cout << "Podaj nazwe nowego budzetu (np. Wakacje): ";
            string nazwa = wczytajLinie();
            listaBudzetow.push_back(Budzet(nazwa));
            cout << "Budzet '" << nazwa << "' zostal utworzony." << endl;
            zapisTransackji(1, nazwa, " ");
            break;
        } //Dodanie nowego budżetu
        case 2: //dodanie konta
        {
            if (listaBudzetow.empty())
            {
                cout << "Najpierw utworz jakis budzet!" << endl;
                break;
            } //sprawdzanie zawartości

            cout << "Wybierz budzet do edycji:" << endl;
            int i = 1;

            Budzety(listaBudzetow); //Wyświetlanie budżetów

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


                cout << "dostępne konta: ";
                if (nazwyKont.empty()) {std::cout << "Lista kont jest pusta." << std::endl;}
                else
                {
                    int idx = 1;
                    for (const auto& nazwa : nazwyKont)
                    {
                        std::cout << idx << ". " << nazwa << " ";
                        idx++;
                    }
                }
                cout << "Podaj miejsce przechowywania: ";
                string miejsce = wczytajLinie();

                bool poprawnosc = nazwaKontaPoprawna(miejsce, nazwyKont);

                if (poprawnosc)
                {
                    it->dodajKonto(kwota, miejsce);
                    cout << "Dodano konto z środkami." << endl;
                    zapisTransackji(1, it->nazwaBudżetu(), miejsce);
                }
                else{cout << "Nieprawidłowa nazwa";}
            } else {cout << "Nieprawidlowy numer." << endl;}
            break;
        } // dodanie konta
        case 3: //wyświetl budzety
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
            } // Wyświetlanie budżetów
        case 4: //zmiana środków w wybranym koncie i budżecie
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
                    cout << i << ". " << b.nazwaBudżetu() << endl;
                    i++;
                }

                int numer;
                cout << "Podaj numer: ";
                cin >> numer;
                cin.ignore();

                if (numer > 0 && numer <= listaBudzetow.size())
                {
                    // Znajdowanie elementu w liście
                    auto it = listaBudzetow.begin();
                    advance(it, numer - 1); // Przesuwamy iterator na wybraną pozycję

                    it->zmianaŚrodków();
                    //cout << "Usunięto środki" << endl;
                } else {cout << "Nieprawidlowy numer." << endl;}


                break;
            } // zmiana środków <- nie dodane zapisu transakcji
        case 5: //usuń konto
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
                    cout << i << ". " << b.nazwaBudżetu() << endl;
                    i++;
                }

                int numer;
                cout << "Podaj numer: ";
                cin >> numer;
                cin.ignore();

                if (numer > 0 && numer <= listaBudzetow.size())
                {
                    // Znajdowanie elementu w liście
                    auto it = listaBudzetow.begin();
                    advance(it, numer - 1); // Przesuwamy iterator na wybraną pozycję

                    string nazwaKonta = it->usunKonto();
                    if (nazwaKonta != "")
                    {
                        cout << "Usunięto środki" << endl;
                        zapisTransackji(4, it->nazwaBudżetu(), nazwaKonta);
                    }
                } else {cout << "Nieprawidlowy numer." << endl;}
                break;
            } // Usuwanie konta
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
                    string Nazwakasowana = it->nazwaBudżetu();
                    listaBudzetow.erase(it);

                    cout << "Budzet '" << Nazwakasowana << "' zostal usuniety." << endl;
                    zapisTransackji(2, Nazwakasowana, " ");
                } else {
                    cout << "Nieprawidlowy numer." << endl;
                }
                break;
            } //Usuwanie budżetu

        case 7: //zmiana dostępnych kont
            {
                modListaKont(nazwyKont);
                break;
            } //Modyfikacja listy nazwa konta <-nie dodałem zapisu transakcji

        case 8: //Wyświetlanie raportu
            {
                raport(listaBudzetow, nazwyKont);
                break;
            }

        case 0:
            zapiszBaze(listaBudzetow, nazwyKont);
            cout << "Konczenie programu..." << endl;

            break;
        default:
            cout << "Nieznana opcja." << endl;
        }

    } while (wybor != 0);

    return 0;
}
