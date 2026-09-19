
# Menedżer Finansów
Aplikacja okienkowa do kompleksowego zarządzania finansami osobistymi, stworzona w języku C++ z wykorzystaniem frameworka Qt. Program wymaga uwierzytelnienia użytkownika poprzez okno logowania. Po pomyślnym zalogowaniu, aplikacja uruchamia główne okno programu (`MainWindow`), oferujące rozbudowany system zakładek do kontroli majątku.
# Główne funkcjonalności
Budżety i Konta: Możliwość tworzenia wielu niezależnych budżetów (np. "Budżet Domowy") oraz przypisywania do nich różnych typów kont: Zwykłe, Oszczędnościowe oraz Obligacje. System obsługuje definiowanie oprocentowania i cykli kapitalizacji, automatycznie przeliczając odsetki przy starcie. Użytkownik może swobodnie wpłacać i wypłacać środki.
Zarządzanie Długami: Moduł pozwalający na ewidencjonowanie zobowiązań (środki do oddania, oznaczane na czerwono) oraz wierzytelności (środki do odzyskania, oznaczane na zielono). Każdy wpis zawiera informacje o osobie, kwocie, dacie i dodatkowy opis. Aplikacja wspiera częściową oraz całkowitą spłatę długów.
Historia Transakcji: Zapis wszystkich kluczowych operacji (tworzenie budżetów, dodawanie kont, zmiany salda) w pliku `historia.csv`. Widok historii pozwala na filtrowanie zdarzeń według typu kategorii oraz wyszukiwanie tekstowe w opisach.
Raport Kont: Globalne zestawienie grupujące środki z kont o tej samej nazwie zlokalizowanych w różnych budżetach, co pozwala na szybki podgląd całkowitych zasobów w danej kategorii.
Obsługa Kaucji i Zasilania: Dedykowane zakładki pozwalające na zarządzanie kaucją (np. z butelek), doładowywanie salda za pomocą kodów oraz wypłacanie zgromadzonej kaucji z bezpośrednim transferem środków do wybranych budżetów głównych.
# Struktura i Architektura
Interfejs Użytkownika: Zbudowany przy użyciu klas Qt, z centralnym elementem `QTabWidget` dzielącym program na sekcje logiczne. Do prezentacji danych wykorzystywane są zagnieżdżone drzewa (`QTreeWidget` dla budżetów) oraz tabele (`QTableWidget` dla długów, historii i raportów).
Zarządzanie Danymi: Informacje o budżetach (`listaBudzetow`), kontach (`nazwyKont`) oraz długach (`listaDlugow`) są wczytywane podczas inicjalizacji okna głównego i automatycznie zapisywane do bazy w destruktorze podczas zamykania programu.
Modułowość: Główne okno integruje zewnętrzne widoki, takie jak `WrzucButelki`, `WyplacSaldo` oraz `DodajSaldo`, łącząc je z głównym interfejsem za pomocą mechanizmu sygnałów i slotów (np. odświeżanie widoku po przelaniu środków).
# Wymagania Techniczne
Kompilator C++ ze wsparciem dla standardu C++11 (lub nowszego).
Biblioteka Qt (wykorzystywane moduły m.in. z `QApplication`, `QMainWindow`, `QDialog`, `QTableWidget`, `QTreeWidget`).
Dostęp do systemu plików (zapis/odczyt konfiguracji bazy danych oraz pliku `historia.csv`).
