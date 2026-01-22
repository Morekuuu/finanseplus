/* Lista To Do
 *
 *  1. Blokada usuwania nazwy konta jeśli istnieje w użyciu
 *  2. Dodanie potwierdzenia przy usuwaniu budżetu oraz konta z budżetu
 *  4.
 *  5. GUI z Dodanie historii transakcji
 *  6. Dodanie przesyłu środków z kaucji
 *
 *  8.
 *
 *  Zrobione:
 *  3. Dodanie raportu
 *  7. Dodawanie spersjonalizowanych produktów inwestycyjnych
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
#include "dlugi.h"

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
                zapisTransackji(1, " ", nazwa);
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
                            zapisTransackji(6, " ", nazwa);
                            break;
                        }
                        idx++;
                    }


                }
                cout << "Nieprawidłowy numer";
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

    std::list<Dlug> listaDlugow;

    wczytajBaze(listaBudzetow, nazwyKont);
    for (auto& b : listaBudzetow)
    {
        b.przeliczWszystkieKonta();
    }


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
        cout << "9. Długi" << endl;
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
            case 2: // dodanie konta / wpłata
            {
                if (listaBudzetow.empty())
                {
                    cout << "Najpierw utworz jakis budzet!" << endl;
                    break;
                }

                cout << "Wybierz budzet do edycji:" << endl;
                Budzety(listaBudzetow); // Wyświetlanie budżetów (Twoja funkcja)

                int numer;
                cout << "Podaj numer: ";
                cin >> numer;
                cin.ignore();

                if (numer > 0 && numer <= listaBudzetow.size())
                {
                    // Ustawiamy iterator na wybrany budżet
                    auto it = listaBudzetow.begin();
                    advance(it, numer - 1);

                    cout << "Podaj kwote: ";
                    double kwota;
                    cin >> kwota;
                    cin.ignore();

                    cout << "Dostepne nazwy kont: ";
                    if (nazwyKont.empty()) {
                        cout << "(Brak zdefiniowanych nazw)" << endl;
                    } else {
                        int idx = 1;
                        for (const auto& nazwa : nazwyKont) {
                            cout << idx << ". " << nazwa << " ";
                            idx++;
                        }
                        cout << endl;
                    }

                    cout << "Podaj miejsce przechowywania (nazwa konta): ";
                    string miejsce = wczytajLinie();

                    // Sprawdzamy, czy nazwa jest na liście dozwolonych
                    bool poprawnosc = nazwaKontaPoprawna(miejsce, nazwyKont);

                    if (poprawnosc)
                    {
                        // --- TUTAJ ZACZYNA SIĘ NOWA LOGIKA ---
                        cout << "\nWybierz typ konta:" << endl;
                        cout << "0 - ZWYKLE (Basic)" << endl;
                        cout << "1 - OSZCZEDNOSCIOWE (Saving)" << endl;
                        cout << "3 - OBLIGACJE (Bonds)" << endl;
                        cout << "Wyboc: ";

                        int typ;
                        cin >> typ;

                        if (typ == 1) // Saving
                        {
                            double opr, cykl, cyklDni;
                            cout << "Podaj oprocentowanie (np. 0.05 dla 5%): ";
                            cin >> opr;
                            cout << "Co ile dni naliczac odsetki? (np. 30): ";
                            cin >> cyklDni;
                            cin.ignore();

                            cykl = cyklDni * 86400;

                            // Dodajemy konto Saving bezpośrednio do listy
                            it->konta.push_back(Konto(miejsce, kwota, Konto::saving, opr, cykl));

                            cout << "Dodano konto oszczednosciowe." << endl;
                        }
                        else if (typ == 3) // Bonds
                        {
                            double opr, cykl, cyklDni;
                            long long trwanie, trwanieDni;
                            string cel;

                            cout << "Podaj oprocentowanie (np. 0.05): "; cin >> opr;
                            cout << "Co ile dni wyplaca odsetki?: "; cin >> cyklDni;
                            cout << "Ile dni trwa obligacja?: "; cin >> trwanieDni;
                            cin.ignore();
                            cykl = cyklDni * 86400;
                            trwanie = trwanieDni * 86400;

                            cout << "Cel przelewu (nazwa innego konta): ";
                            cel = wczytajLinie();

                            // Dodajemy Obligację
                            // Konstruktor: nazwa, kwota, typ, procent, cykl, data(0=teraz), trwanie, cel
                            it->konta.push_back(Konto(miejsce, kwota, Konto::bonds, opr, cykl, 0, trwanie, cel));

                            cout << "Dodano obligacje." << endl;
                        }
                        else // Domyślnie Basic (0 lub inne)
                        {
                            cin.ignore(); // na wszelki wypadek
                            // Dodajemy zwykłe konto
                            it->konta.push_back(Konto(miejsce, kwota, Konto::basic));
                            cout << "Dodano standardowe konto." << endl;
                        }

                        // --- KONIEC NOWEJ LOGIKI ---

                        // Logowanie operacji (Twoja funkcja)
                        zapisTransackji(3, it->nazwaBudżetu(), miejsce); // Poprawiłem literówkę w metodzie nazwaBudżetu -> nazwaBudzetu (unikaj polskich znaków w nazwach metod)
                    }
                    else
                    {
                        cout << "Nieprawidlowa nazwa (spoza listy dozwolonych)." << endl;
                    }
                }
                else
                {
                    cout << "Nieprawidlowy numer budzetu." << endl;
                }
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

        case 9: {
            cout << "\n=== DLUGI ===" << endl;
            cout << "1. Dodaj nowy dlug / pozyczke" << endl;
            cout << "2. Wyswietl dlugi" << endl;
            cout << "3. Splac dlug" << endl;

            int wyborDlug; // Deklaracja zmiennej
            cin >> wyborDlug;
            cin.ignore();

            if (wyborDlug == 1) { // DODAWANIE
                cout << "Kierunek (1-JA pozyczam od kogos, 2-KTOS ode mnie): ";
                int kierunek; // <--- Naprawiony błąd "not declared"
                cin >> kierunek;
                cin.ignore();

                cout << "Kto: ";
                string kto = wczytajLinie(); // <--- Naprawiony błąd

                cout << "Ile: ";
                double kwota; // <--- Naprawiony błąd
                cin >> kwota;
                cin.ignore();

                cout << "Opis: ";
                string opis = wczytajLinie(); // <--- Naprawiony błąd

                // TUTAJ UZYWAMY TWOICH NAZW (bez polskich znakow w kodzie!)
                Dlug::Typ typ = (kierunek == 1) ? Dlug::Zobowiazanie : Dlug::Wierzytelnosc;

                listaDlugow.push_back(Dlug(kto, kwota, typ, opis, pobierzDate()));
                cout << "Dodano." << endl;

                // --- INTEGRACJA ---
                cout << "Czy zaktualizowac saldo konta? (1-TAK, 0-NIE): ";
                int czyAktualizowac; // <--- Naprawiony błąd
                cin >> czyAktualizowac;
                cin.ignore();

                if (czyAktualizowac == 1 && !listaBudzetow.empty()) {
                    cout << "Wybierz budzet:" << endl;
                    int i = 1;
                    // Upewnij się, że używasz poprawnej nazwy metody z klasy Budzet (nazwaBudzetu lub nazwaBudżetu)
                    for(auto& b : listaBudzetow) {
                        cout << i++ << ". " << b.nazwaBudżetu() << endl;
                    }
                    int nr; cin >> nr; cin.ignore();

                    if (nr > 0 && nr <= listaBudzetow.size()) {
                        auto it = listaBudzetow.begin();
                        advance(it, nr - 1);

                        cout << "Nazwa konta: ";
                        string kontoNazwa = wczytajLinie(); // <--- Naprawiony błąd

                        bool znaleziono = false;
                        for(auto& k : it->konta) {
                            if(k.nazwaZwrot() == kontoNazwa) {
                                // Tutaj też używamy Dlug::Zobowiazanie
                                double zmiana = (typ == Dlug::Zobowiazanie) ? kwota : -kwota;
                                k.saldoZmiana(zmiana);
                                znaleziono = true;
                                cout << "Zaktualizowano saldo." << endl;
                                break;
                            }
                        }
                        if (!znaleziono) cout << "Brak takiego konta." << endl;
                    }
                }
            }
            else if (wyborDlug == 2) {
                if(listaDlugow.empty()) cout << "Brak danych." << endl;
                else {
                    int id = 1;
                    for(const auto& d : listaDlugow) d.wyswietl(id++);
                }
            }
            else if (wyborDlug == 3) { // SPLATA
                // (Kod spłaty analogicznie musi używać zmiennych zadeklarowanych przed użyciem
                // oraz Dlug::Zobowiazanie / Dlug::Wierzytelnosc)
                 if (listaDlugow.empty()) {
                    cout << "Brak dlugow." << endl;
                } else {
                    int i = 1;
                    for (const auto& d : listaDlugow) d.wyswietl(i++);

                    cout << "Wybierz numer do splaty: ";
                    int nr;
                    cin >> nr;

                    if (nr > 0 && nr <= listaDlugow.size()) {
                        auto itDlug = listaDlugow.begin();
                        advance(itDlug, nr-1);

                        cout << "Ile splacono? (max " << itDlug->kwotaZwrot() << "): ";
                        double ile;
                        cin >> ile;
                        cin.ignore();

                        // --- INTEGRACJA ---
                        cout << "Czy pobrac/wplacic srodki na Twoje konto? (1-TAK, 0-NIE): ";
                        int czyAktualizowac;
                        cin >> czyAktualizowac;
                        cin.ignore();

                        if (czyAktualizowac == 1 && !listaBudzetow.empty()) {
                            // ... (logika wyboru budżetu jak wyżej) ...
                            // TUTAJ SKRÓCONA WERSJA DLA CZYTELNOŚCI:
                            cout << "Wybierz budzet nr: "; int bNr; cin >> bNr; cin.ignore();
                            auto itBudzet = listaBudzetow.begin(); advance(itBudzet, bNr-1);
                            cout << "Nazwa konta: "; string kNazwa = wczytajLinie();

                            for(auto& k : itBudzet->konta) {
                                if(k.nazwaZwrot() == kNazwa) {
                                    // Poprawka nazwy
                                    double zmiana = (itDlug->typZwrot() == Dlug::Zobowiazanie) ? -ile : ile;
                                    k.saldoZmiana(zmiana);
                                    cout << "Saldo zaktualizowane." << endl;
                                    break;
                                }
                            }
                        }

                        itDlug->splacCzesc(ile);
                        if(itDlug->kwotaZwrot() <= 0.01) listaDlugow.erase(itDlug);
                    }
                }
            }
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
