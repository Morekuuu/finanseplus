#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include "budzet.h"
#include "dlugi.h"

class WrzucButelki;
class DodajSaldo;
class WyplacSaldo;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Sloty dla Budżetów
    void onDodajBudzet();
    void onUsunBudzet();
    void onDodajKonto();
    void onUsunKonto();
    void onZmienSrodki();

    //Sloty dla Długów
    void onDodajDlug();
    void onSplacDlug();

    //Sloty dla Historii
    void onFiltrujHistorie();
    void wczytajHistorieZCSV();

    //Slot dla Raportu
    void generujRaport();

private:
    // Listy
    std::list<Budzet> listaBudzetow;
    std::list<std::string> nazwyKont;
    std::list<Dlug> listaDlugow;

    // UI COMPONENTS
    QTabWidget *mainTabWidget;

    // Zakładka 1: Budżety
    QWidget *tabBudzety;
    QTreeWidget *treeBudzety;
    QPushButton *btnDodajBudzet;
    QPushButton *btnUsunBudzet;
    QPushButton *btnDodajKonto;
    QPushButton *btnUsunKonto;
    QPushButton *btnZmienSrodki;
    QLabel *lblSumaCalkowita;

    // Zakładka 2: Długi
    QWidget *tabDlugi;
    QTableWidget *tableDlugi;
    QPushButton *btnDodajDlug;
    QPushButton *btnSplacDlug;

    // Zakładka 3: Historia
    QWidget *tabHistoria;
    QTableWidget *tableHistoria;
    QComboBox *comboFiltrRodzaj;
    QLineEdit *txtSzukaj;
    QLabel *lblSumaHistorii;

    // Zakładka 4: Raport
    QWidget *tabRaport;
    QTableWidget *tableRaport;
    QLabel *lblSumaRaport;

    // Zakładka 5: Kaucja - Wrzut butelek
    QWidget *tabKaucja;
    WrzucButelki *wrzutWidget;

    // Zakładka 6: Kaucja - Dodaj saldo
    DodajSaldo *dodajSaldoWidget;
    // Zakładka 7: Kaucja - Wypłać Saldo
    WyplacSaldo *wyplacSaldoWidget;

    // Metody pomocnicze
    void odswiezWidokBudzetow();
    void odswiezWidokDlugow();
    void setupUi();
    void zapiszDane();
};

#endif
