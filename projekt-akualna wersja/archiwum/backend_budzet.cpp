#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <fstream>

using namespace std;

const string NAZWA_PLIKU = "budzety.txt";

// Struktura reprezentująca pojedyncze miejsce przechowywania pieniędzy w danym budżecie
struct Konto {
    double kwota;
    string lokalizacja; // np. "Bank PKO", "Portfel"

    Konto(double k, string l) : kwota(k), lokalizacja(l) {}
};

// Klasa reprezentująca jeden budżet tematyczny (np. "Wakacje")
class Budzet {
public:
    string nazwa;
    list<Konto> konta; // Lista kont wewnątrz tego budżetu

    Budzet(string n) : nazwa(n) {}

    // Metoda dodająca nową kwotę i miejsce do budżetu
    void dodajSrodki(double kwota, string lokalizacja) {
        konta.push_back(Konto(kwota, lokalizacja));
    }

    // Metoda obliczająca sumę w danym budżecie
    double sumaCalkowita() const {
        double suma = 0;
        for (const auto& konto : konta) {
            suma += konto.kwota;
        }
        return suma;
    }

    // Wyświetlanie szczegółów budżetu
    void wyswietl() const {
        cout << "=== Budzet: " << nazwa << " ===" << endl;
        if (konta.empty()) {
            cout << "  (Brak srodkow)" << endl;
        } else {
            for (const auto& konto : konta) {
                cout << "  - " << konto.lokalizacja << ": "
                     << fixed << setprecision(2) << konto.kwota << " PLN" << endl;
            }
            cout << "  SUMA: " << fixed << setprecision(2) << sumaCalkowita() << " PLN" << endl;
        }
        cout << "-------------------------" << endl;
    }
};

// Funkcja pomocnicza do pobierania linii tekstu (radzi sobie ze spacjami)
string wczytajLinie() {
    string tekst;
    getline(cin, tekst);
    return tekst;
}
void zapiszBaze(const list<Budzet>& lista) {
    ofstream plik(NAZWA_PLIKU); // Otwieramy plik do zapisu

    if (plik.is_open()) {
        // Najpierw zapisujemy ile mamy budżetów
        plik << lista.size() << endl;

        for (const auto& budzet : lista) {
            // Zapisujemy nazwę budżetu
            plik << budzet.nazwa << endl;
            // Zapisujemy ile kont ma ten budżet
            plik << budzet.konta.size() << endl;

            for (const auto& konto : budzet.konta) {
                // Zapisujemy dane konta: lokalizacja i kwota
                plik << konto.lokalizacja << endl;
                plik << konto.kwota << endl;
            }
        }
        plik.close();
        cout << "[INFO] Dane zostaly zapisane do pliku " << NAZWA_PLIKU << endl;
    } else {
        cout << "[BLAD] Nie udalo sie otworzyc pliku do zapisu!" << endl;
    }
}

void wczytajBaze(list<Budzet>& lista) {
    ifstream plik(NAZWA_PLIKU); // Otwieramy plik do odczytu

    if (plik.is_open()) {
        int iloscBudzetow;
        plik >> iloscBudzetow;
        plik.ignore(); // Ignorujemy znak nowej linii po wczytaniu liczby

        for (int i = 0; i < iloscBudzetow; i++) {
            string nazwaBudzetu;
            getline(plik, nazwaBudzetu); // Wczytujemy nazwę budżetu (może mieć spacje)

            Budzet nowyBudzet(nazwaBudzetu);

            int iloscKont;
            plik >> iloscKont;
            plik.ignore(); // Znów ignorujemy nową linię po liczbie

            for (int j = 0; j < iloscKont; j++) {
                string lokalizacja;
                double kwota;

                getline(plik, lokalizacja);
                plik >> kwota;
                plik.ignore(); // Ignorujemy nową linię po kwocie

                nowyBudzet.dodajSrodki(kwota, lokalizacja);
            }
            lista.push_back(nowyBudzet);
        }
        plik.close();
        cout << "[INFO] Wczytano dane z pliku (" << lista.size() << " budzetow)." << endl;
    } else {
        cout << "[INFO] Brak pliku zapisu lub pierwszy start programu." << endl;
    }
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
