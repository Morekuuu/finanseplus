#include "mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFormLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QBrush>
#include "baza_danych.h"
#include "dlugi.h"
#include "wrzucbutelki.h"
#include "dodajsaldo.h"
#include "wyplacsaldo.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 1. Wczytanie danych
    wczytajBaze(listaBudzetow, nazwyKont);
    wczytajDlugi(listaDlugow);

    //Przeliczenie odsetek
    for (auto& b : listaBudzetow) {
        b.przeliczWszystkieKonta();
    }

    // 2. Budowa Interfejsu
    setupUi();

    // 3. Pierwsze odświeżenie widoków
    odswiezWidokBudzetow();
    odswiezWidokDlugow();
    wczytajHistorieZCSV();
    generujRaport();
}

MainWindow::~MainWindow()
{
    zapiszDane();
}

void MainWindow::zapiszDane()
{
    zapiszBaze(listaBudzetow, nazwyKont);
    zapiszDlugi(listaDlugow);
}

void MainWindow::setupUi()
{
    resize(1000, 700);
    setWindowTitle("Menedżer Finansów");

    mainTabWidget = new QTabWidget(this);
    setCentralWidget(mainTabWidget);

    // ----------------------------- Zakładka - Budżety ----------------------------------
    tabBudzety = new QWidget();
    QVBoxLayout *layoutBudzety = new QVBoxLayout(tabBudzety);

    treeBudzety = new QTreeWidget();
    treeBudzety->setHeaderLabels({"Nazwa", "Saldo", "Typ / Oprocentowanie"});
    treeBudzety->setColumnWidth(0, 300);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnDodajBudzet = new QPushButton("Dodaj Budżet");
    btnUsunBudzet = new QPushButton("Usuń Budżet");
    btnDodajKonto = new QPushButton("Dodaj Konto");
    btnUsunKonto = new QPushButton("Usuń Konto");
    btnZmienSrodki = new QPushButton("Wpłać / Wypłać");

    btnLayout->addWidget(btnDodajBudzet);
    btnLayout->addWidget(btnUsunBudzet);
    btnLayout->addWidget(btnDodajKonto);
    btnLayout->addWidget(btnUsunKonto);
    btnLayout->addWidget(btnZmienSrodki);

    lblSumaCalkowita = new QLabel("Całkowity majątek: 0.00 PLN");
    QFont font = lblSumaCalkowita->font();
    font.setBold(true);
    font.setPointSize(12);
    lblSumaCalkowita->setFont(font);

    layoutBudzety->addWidget(treeBudzety);
    layoutBudzety->addWidget(lblSumaCalkowita);
    layoutBudzety->addLayout(btnLayout);

    mainTabWidget->addTab(tabBudzety, "Budżety i Konta");

    // ----------------------------- Zakładka - Długi ----------------------------------
    tabDlugi = new QWidget();
    QVBoxLayout *layoutDlugi = new QVBoxLayout(tabDlugi);

    tableDlugi = new QTableWidget();
    tableDlugi->setColumnCount(5);
    tableDlugi->setHorizontalHeaderLabels({"Kto", "Kwota", "Typ", "Data", "Opis"});
    tableDlugi->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout *btnLayoutDlugi = new QHBoxLayout();
    btnDodajDlug = new QPushButton("Dodaj Dług/Zobowiązanie");
    btnSplacDlug = new QPushButton("Spłać wybrany");
    btnLayoutDlugi->addWidget(btnDodajDlug);
    btnLayoutDlugi->addWidget(btnSplacDlug);

    layoutDlugi->addWidget(tableDlugi);
    layoutDlugi->addLayout(btnLayoutDlugi);

    mainTabWidget->addTab(tabDlugi, "Długi");

    // ----------------------------- Zakładka - Historia ----------------------------------
    tabHistoria = new QWidget();
    QVBoxLayout *layoutHistoria = new QVBoxLayout(tabHistoria);

    QHBoxLayout *filtersLayout = new QHBoxLayout();
    comboFiltrRodzaj = new QComboBox();
    comboFiltrRodzaj->addItem("Wszystkie");
    comboFiltrRodzaj->addItem("Dodano nowy budżet");
    comboFiltrRodzaj->addItem("Dodano nowe konto");
    comboFiltrRodzaj->addItem("Wpłata/Wypłata");

    txtSzukaj = new QLineEdit();
    txtSzukaj->setPlaceholderText("Szukaj w opisie...");

    QPushButton *btnOdswiezHist = new QPushButton("Odśwież Historię");

    filtersLayout->addWidget(new QLabel("Filtr:"));
    filtersLayout->addWidget(comboFiltrRodzaj);
    filtersLayout->addWidget(txtSzukaj);
    filtersLayout->addWidget(btnOdswiezHist);

    tableHistoria = new QTableWidget();
    tableHistoria->setColumnCount(4);
    tableHistoria->setHorizontalHeaderLabels({"Data", "Opis Zdarzenia", "Budżet/Kategoria", "Konto/Szczegóły"});
    tableHistoria->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    lblSumaHistorii = new QLabel("Liczba transakcji: 0");

    layoutHistoria->addLayout(filtersLayout);
    layoutHistoria->addWidget(tableHistoria);
    layoutHistoria->addWidget(lblSumaHistorii);

    mainTabWidget->addTab(tabHistoria, "Historia Transakcji");

    // ----------------------------- Zakładka - raport kont ----------------------------------
    tabRaport = new QWidget();
    QVBoxLayout *layoutRaport = new QVBoxLayout(tabRaport);

    tableRaport = new QTableWidget();
    tableRaport->setColumnCount(2);
    tableRaport->setHorizontalHeaderLabels({"Nazwa Konta (Globalna)", "Łączna suma środków"});
    tableRaport->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *btnOdswiezRaport = new QPushButton("Odśwież Raport");
    lblSumaRaport = new QLabel("Suma wszystkich środków: 0.00 PLN");
    lblSumaRaport->setFont(font);

    layoutRaport->addWidget(new QLabel("Poniższa lista sumuje środki z kont o tej samej nazwie we wszystkich budżetach."));
    layoutRaport->addWidget(tableRaport);
    layoutRaport->addWidget(lblSumaRaport);
    layoutRaport->addWidget(btnOdswiezRaport);

    mainTabWidget->addTab(tabRaport, "Raport Kont");


    // ----------------------------- Zakładka - Kaucja ----------------------------------
    QWidget *tabKaucja = new QWidget();
    QVBoxLayout *layoutKaucja = new QVBoxLayout(tabKaucja);

    WrzucButelki *wrzut = new WrzucButelki(tabKaucja);   // UI z wrzucbutelki.ui
    layoutKaucja->addWidget(wrzut);

    mainTabWidget->addTab(tabKaucja, "Kaucja");

    if (listaBudzetow.empty()) {
        listaBudzetow.push_back(Budzet("Budżet Domowy"));
    }

    wyplacSaldoWidget = new WyplacSaldo(&listaBudzetow, this);
    mainTabWidget->addTab(wyplacSaldoWidget, "Wypłać Kaucję");
    connect(wyplacSaldoWidget, &WyplacSaldo::srodkiPrzelane, this, [this](){
        this->odswiezWidokBudzetow();
        this->generujRaport();
    });


    // ----------------------------- Zakładka - Dodaj Saldo (Kaucja) -----------------------------
    dodajSaldoWidget = new DodajSaldo(this);
    mainTabWidget->addTab(dodajSaldoWidget, "Dodaj saldo (kody)");

    // Podłączenia syngałów
    connect(btnDodajBudzet, &QPushButton::clicked, this, &MainWindow::onDodajBudzet);
    connect(btnUsunBudzet, &QPushButton::clicked, this, &MainWindow::onUsunBudzet);
    connect(btnDodajKonto, &QPushButton::clicked, this, &MainWindow::onDodajKonto);
    connect(btnUsunKonto, &QPushButton::clicked, this, &MainWindow::onUsunKonto);
    connect(btnZmienSrodki, &QPushButton::clicked, this, &MainWindow::onZmienSrodki);

    connect(btnDodajDlug, &QPushButton::clicked, this, &MainWindow::onDodajDlug);
    connect(btnSplacDlug, &QPushButton::clicked, this, &MainWindow::onSplacDlug);

    connect(btnOdswiezHist, &QPushButton::clicked, this, &MainWindow::wczytajHistorieZCSV);
    connect(comboFiltrRodzaj, &QComboBox::currentTextChanged, this, &MainWindow::onFiltrujHistorie);
    connect(txtSzukaj, &QLineEdit::textChanged, this, &MainWindow::onFiltrujHistorie);

    //Sygnał Raportu
    connect(btnOdswiezRaport, &QPushButton::clicked, this, &MainWindow::generujRaport);
    connect(mainTabWidget, &QTabWidget::currentChanged, this, [this](int index){
        if (mainTabWidget->tabText(index) == "Raport Kont") {
            generujRaport();
        }
    });
}

// ----------------------------- sekcja - Budżety ----------------------------------

void MainWindow::odswiezWidokBudzetow()
{
    treeBudzety->clear();
    double sumaWszystkiego = 0.0;

    for (const auto& budzet : listaBudzetow)
    {
        QTreeWidgetItem *budzetItem = new QTreeWidgetItem(treeBudzety);
        budzetItem->setText(0, QString::fromStdString(budzet.nazwaBudżetu()));
        budzetItem->setText(1, QString::number(budzet.sumaCalkowita(), 'f', 2) + " PLN");

        sumaWszystkiego += budzet.sumaCalkowita();

        for (const auto& konto : budzet.konta)
        {
            QTreeWidgetItem *kontoItem = new QTreeWidgetItem(budzetItem);
            kontoItem->setText(0, QString::fromStdString(konto.nazwaZwrot()));
            kontoItem->setText(1, QString::number(konto.saldoZwrot(), 'f', 2) + " PLN");

            QString opisTypu;
            switch(konto.rodzajZwrot())
            {
            case Konto::basic: opisTypu = "Zwykłe"; break;
            case Konto::saving: opisTypu = "Oszczędnościowe (" + QString::number(konto.oprocentowanieZwrot()*100) + "%)"; break;
            case Konto::bonds: opisTypu = "Obligacje"; break;
            default: opisTypu = "Inne";
            }
            kontoItem->setText(2, opisTypu);
        }
    }
    treeBudzety->expandAll();
    lblSumaCalkowita->setText("Całkowity majątek: " + QString::number(sumaWszystkiego, 'f', 2) + " PLN");
}

void MainWindow::onDodajBudzet()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Nowy Budżet", "Nazwa budżetu:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty())
    {
        listaBudzetow.push_back(Budzet(text.toStdString()));
        zapisTransackji(1, text.toStdString(), "");
        odswiezWidokBudzetow();
    }
}

void MainWindow::onUsunBudzet()
{
    QTreeWidgetItem *current = treeBudzety->currentItem();
    if (!current || current->parent())
    {
        QMessageBox::warning(this, "Błąd", "Wybierz nazwę budżetu (główną gałąź) do usunięcia.");
        return;
    }

    std::string nazwa = current->text(0).toStdString();
    auto it = std::find_if(listaBudzetow.begin(), listaBudzetow.end(),
                           [&](const Budzet& b){ return b.nazwaBudżetu() == nazwa; });

    if (it != listaBudzetow.end())
    {
        listaBudzetow.erase(it);
        zapisTransackji(2, nazwa, "");
        odswiezWidokBudzetow();
    }
}

void MainWindow::onDodajKonto()
{
    QTreeWidgetItem *current = treeBudzety->currentItem();
    if (!current) {
        QMessageBox::warning(this, "Błąd", "Wybierz budżet, do którego chcesz dodać konto.");
        return;
    }
    if (current->parent()) current = current->parent();

    std::string nazwaBudzetu = current->text(0).toStdString();
    auto itBudzet = std::find_if(listaBudzetow.begin(), listaBudzetow.end(),
                                 [&](const Budzet& b){ return b.nazwaBudżetu() == nazwaBudzetu; });
    if (itBudzet == listaBudzetow.end()) return;

    QDialog dialog(this);
    dialog.setWindowTitle("Dodaj Konto");
    QFormLayout form(&dialog);

    QLineEdit *editNazwa = new QLineEdit(&dialog);
    QDoubleSpinBox *spinKwota = new QDoubleSpinBox(&dialog);
    spinKwota->setRange(0, 10000000);
    QComboBox *comboTyp = new QComboBox(&dialog);
    comboTyp->addItem("Zwykłe", Konto::basic);
    comboTyp->addItem("Oszczędnościowe", Konto::saving);
    comboTyp->addItem("Obligacje", Konto::bonds);

    QDoubleSpinBox *spinOprocentowanie = new QDoubleSpinBox(&dialog);
    spinOprocentowanie->setSingleStep(0.01);
    QSpinBox *spinCykl = new QSpinBox(&dialog);
    spinCykl->setRange(1, 3650);
    spinCykl->setValue(30);

    form.addRow("Nazwa konta:", editNazwa);
    form.addRow("Kwota startowa:", spinKwota);
    form.addRow("Typ:", comboTyp);
    form.addRow("Oprocentowanie (ułamek, np 0.05):", spinOprocentowanie);
    form.addRow("Cykl odsetek (dni):", spinCykl);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        std::string nazwaKonta = editNazwa->text().toStdString();
        if (nazwaKonta.empty()) return;

        double kwota = spinKwota->value();
        Konto::rodzaj typ = (Konto::rodzaj)comboTyp->currentData().toInt();
        double opr = spinOprocentowanie->value();
        double cykl = spinCykl->value() * 86400;

        bool juzJest = false;
        for(const auto& n : nazwyKont) if(n == nazwaKonta) juzJest = true;
        if(!juzJest) nazwyKont.push_back(nazwaKonta);

        if (typ == Konto::saving) {
            itBudzet->konta.push_back(Konto(nazwaKonta, kwota, typ, opr, cykl));
        } else if (typ == Konto::bonds) {
            itBudzet->konta.push_back(Konto(nazwaKonta, kwota, typ, opr, cykl, 0, cykl*12, ""));
        } else {
            itBudzet->konta.push_back(Konto(nazwaKonta, kwota, typ));
        }

        zapisTransackji(3, nazwaBudzetu, nazwaKonta);
        odswiezWidokBudzetow();
    }
}

void MainWindow::onUsunKonto()
{
    QTreeWidgetItem *current = treeBudzety->currentItem();
    if (!current || !current->parent())
    {
        QMessageBox::warning(this, "Błąd", "Wybierz konkretne konto do usunięcia.");
        return;
    }

    std::string nazwaBudzetu = current->parent()->text(0).toStdString();
    std::string nazwaKonta = current->text(0).toStdString();

    auto itBudzet = std::find_if(listaBudzetow.begin(), listaBudzetow.end(),
                                 [&](const Budzet& b){ return b.nazwaBudżetu() == nazwaBudzetu; });

    if (itBudzet != listaBudzetow.end())
    {
        auto& k = itBudzet->konta;
        auto itKonto = std::find_if(k.begin(), k.end(), [&](const Konto& ko){ return ko.nazwaZwrot() == nazwaKonta; });

        if (itKonto != k.end())
        {
            k.erase(itKonto);
            zapisTransackji(4, nazwaBudzetu, nazwaKonta);
            odswiezWidokBudzetow();
        }
    }
}

void MainWindow::onZmienSrodki()
{
    QTreeWidgetItem *current = treeBudzety->currentItem();
    if (!current || !current->parent())
    {
        QMessageBox::warning(this, "Błąd", "Wybierz konto, aby zmienić środki.");
        return;
    }

    bool ok;
    double val = QInputDialog::getDouble(this, "Zmiana środków",
                                         "Podaj kwotę (+ dodaje, - odejmuje):", 0, -1000000, 1000000, 2, &ok);
    if (ok && val != 0) {
        std::string nazwaBudzetu = current->parent()->text(0).toStdString();
        std::string nazwaKonta = current->text(0).toStdString();

        for (auto& b : listaBudzetow)
        {
            if (b.nazwaBudżetu() == nazwaBudzetu)
            {
                for (auto& k : b.konta) {
                    if (k.nazwaZwrot() == nazwaKonta)
                    {
                        k.saldoZmiana(val);
                        if (val > 0) zapisTransackji(8, nazwaBudzetu, nazwaKonta + " (+" + std::to_string(val) + ")");
                        else zapisTransackji(7, nazwaBudzetu, nazwaKonta + " (" + std::to_string(val) + ")");
                    }
                }
            }
        }
        odswiezWidokBudzetow();
    }
}

// ---------------------Sekcja długów--------------------------------------

void MainWindow::odswiezWidokDlugow()
{
    tableDlugi->setRowCount(0);
    int row = 0;
    for (const auto& d : listaDlugow)
    {
        tableDlugi->insertRow(row);
        tableDlugi->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.ktoZwrot())));
        tableDlugi->setItem(row, 1, new QTableWidgetItem(QString::number(d.kwotaZwrot(), 'f', 2)));

        QString typStr = (d.typZwrot() == Dlug::Zobowiazanie) ? "Muszę oddać" : "Musi mi oddać";
        QTableWidgetItem* typItem = new QTableWidgetItem(typStr);

        if (d.typZwrot() == Dlug::Zobowiazanie) typItem->setForeground(QBrush(Qt::red));
        else typItem->setForeground(QBrush(Qt::green));

        tableDlugi->setItem(row, 2, typItem);
        tableDlugi->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.dataZwrot())));
        tableDlugi->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(d.opisZwrot())));
        row++;
    }
}

void MainWindow::onDodajDlug()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit *editKto = new QLineEdit(&dialog);
    QDoubleSpinBox *spinKwota = new QDoubleSpinBox(&dialog);
    spinKwota->setRange(0.01, 1000000);
    QComboBox *comboTyp = new QComboBox(&dialog);
    comboTyp->addItem("Ja pożyczam OD kogoś (Zobowiązanie)", Dlug::Zobowiazanie);
    comboTyp->addItem("Ktoś pożycza ODE mnie (Wierzytelność)", Dlug::Wierzytelnosc);
    QLineEdit *editOpis = new QLineEdit(&dialog);

    form.addRow("Osoba:", editKto);
    form.addRow("Kwota:", spinKwota);
    form.addRow("Typ:", comboTyp);
    form.addRow("Opis:", editOpis);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        Dlug::Typ t = (Dlug::Typ)comboTyp->currentData().toInt();
        listaDlugow.push_back(Dlug(editKto->text().toStdString(),
                                   spinKwota->value(),
                                   t,
                                   editOpis->text().toStdString(),
                                   pobierzDate()));
        odswiezWidokDlugow();
        zapiszDlugi(listaDlugow);
    }
}

void MainWindow::onSplacDlug()
{
    int row = tableDlugi->currentRow();
    if (row < 0 || row >= listaDlugow.size()) return;

    auto it = listaDlugow.begin();
    std::advance(it, row);

    bool ok;
    double ile = QInputDialog::getDouble(this, "Spłata", "Ile spłacono?", 0, 0, it->kwotaZwrot(), 2, &ok);
    if (ok)
    {
        it->splacCzesc(ile);
        if (it->kwotaZwrot() <= 0.01)
        {
            listaDlugow.erase(it);
        }
        odswiezWidokDlugow();
        zapiszDlugi(listaDlugow);
    }
}

// ---------------------- Sekcja historii ------------------------

void MainWindow::wczytajHistorieZCSV()
{
    tableHistoria->setRowCount(0);

    QFile file("historia.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        if (fields.size() >= 4)
        {
            int row = tableHistoria->rowCount();
            tableHistoria->insertRow(row);
            tableHistoria->setItem(row, 0, new QTableWidgetItem(fields[0]));
            tableHistoria->setItem(row, 1, new QTableWidgetItem(fields[1]));
            tableHistoria->setItem(row, 2, new QTableWidgetItem(fields[2]));
            tableHistoria->setItem(row, 3, new QTableWidgetItem(fields[3]));
        }
    }
    file.close();
    onFiltrujHistorie();
}

void MainWindow::onFiltrujHistorie()
{
    QString szukaj = txtSzukaj->text().toLower();
    QString kategoria = comboFiltrRodzaj->currentText();

    int widoczneWiersze = 0;

    for (int i = 0; i < tableHistoria->rowCount(); ++i)
    {
        bool pokaz = true;
        QString opis = tableHistoria->item(i, 1)->text().toLower();

        if (!szukaj.isEmpty() && !opis.contains(szukaj))
        {
            pokaz = false;
        }

        if (kategoria != "Wszystkie")
        {
            if (kategoria == "Dodano nowy budżet" && !opis.contains("budżet")) pokaz = false;
            if (kategoria == "Dodano nowe konto" && !opis.contains("nowe konto")) pokaz = false;
        }

        tableHistoria->setRowHidden(i, !pokaz);
        if (pokaz) widoczneWiersze++;
    }

    lblSumaHistorii->setText("Wyświetlono transakcji: " + QString::number(widoczneWiersze));
}

// -------------------------- Sekcja raportu ----------------------------

void MainWindow::generujRaport()
{
    tableRaport->setRowCount(0);
    double sumaCalkowita = 0.0;

    for (const auto& szukanaNazwa : nazwyKont)
    {
        double sumaDlaKategorii = 0.0;
        bool znaleziono = false;

        for (auto& obecnyBudzet : listaBudzetow)
        {
            for (auto& konto : obecnyBudzet.konta)
            {
                if (konto.nazwaZwrot() == szukanaNazwa)
                {
                    sumaDlaKategorii += konto.saldoZwrot();
                    znaleziono = true;
                }
            }
        }
        if (znaleziono)
        {
            int row = tableRaport->rowCount();
            tableRaport->insertRow(row);
            tableRaport->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(szukanaNazwa)));
            tableRaport->setItem(row, 1, new QTableWidgetItem(QString::number(sumaDlaKategorii, 'f', 2) + " PLN"));
            sumaCalkowita += sumaDlaKategorii;
        }
    }

    lblSumaRaport->setText("Suma wszystkich środków: " + QString::number(sumaCalkowita, 'f', 2) + " PLN");
}
