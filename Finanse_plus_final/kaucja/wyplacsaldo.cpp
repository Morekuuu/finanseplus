#include "wyplacsaldo.h"
#include "ui_wyplacsaldo.h"
#include "dodajsaldo.h" // Dostęp do static int saldo
#include <QMessageBox>
#include <QShowEvent> // Ważne do showEvent

WyplacSaldo::WyplacSaldo(std::list<Budzet> *lista, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WyplacSaldo)
    , listaBudzetow(lista)
{
    ui->setupUi(this);

    // Połączenie sygnału zmiany wyboru w ComboBoxie ze slotem
    // Używamy QOverload, bo currentIndexChanged ma dwie wersje (int i QString)
    connect(ui->comboBoxBudzet, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &WyplacSaldo::on_comboBoxBudzet_currentIndexChanged);
}

WyplacSaldo::~WyplacSaldo()
{
    delete ui;
}

void WyplacSaldo::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    odswiezUI(); // Odświeżamy dane przy każdym wejściu w zakładkę
}

void WyplacSaldo::odswiezUI()
{
    // 1. Wyświetl aktualne saldo KAUCJI
    ui->labelAktualneSaldo->setText(
        "Dostępne środki z kaucji: " + QString::number(DodajSaldo::saldo, 'f', 2) + " zł"
        );

    // 2. Jeśli lista budżetów nie istnieje, przerwij
    if (!listaBudzetow) return;

    // 3. Odśwież listę budżetów w ComboBox
    ui->comboBoxBudzet->blockSignals(true); // Blokujemy sygnały, by nie wywoływać slotu podczas czyszczenia
    ui->comboBoxBudzet->clear();

    for (const auto& budzet : *listaBudzetow) {
        ui->comboBoxBudzet->addItem(QString::fromStdString(budzet.nazwaBudżetu()));
    }
    ui->comboBoxBudzet->blockSignals(false);

    // Jeśli są jakieś budżety, wymuś odświeżenie kont dla pierwszego z nich
    if (ui->comboBoxBudzet->count() > 0) {
        // Jeśli nic nie jest wybrane, wybierz pierwszy (to wywoła on_comboBoxBudzet_currentIndexChanged)
        if (ui->comboBoxBudzet->currentIndex() == -1) {
            ui->comboBoxBudzet->setCurrentIndex(0);
        } else {
            // Jeśli coś jest wybrane, ręcznie odśwież konta
            on_comboBoxBudzet_currentIndexChanged(ui->comboBoxBudzet->currentIndex());
        }
    }
}

void WyplacSaldo::on_comboBoxBudzet_currentIndexChanged(int index)
{
    ui->comboBoxKonto->clear();

    // Zabezpieczenia
    if (index < 0 || !listaBudzetow || (size_t)index >= listaBudzetow->size()) return;

    // Znajdź wybrany budżet na liście
    auto it = listaBudzetow->begin();
    std::advance(it, index);

    // Wypełnij drugi ComboBox kontami z tego budżetu
    for (const auto& konto : it->konta) {
        ui->comboBoxKonto->addItem(QString::fromStdString(konto.nazwaZwrot()));
    }
}

void WyplacSaldo::on_pushButtonZatwierdz_clicked()
{
    double kwota = ui->doubleSpinBox->value();

    // Walidacja danych
    if (kwota <= 0) {
        ui->labelWyplacono->setText("Podaj kwotę większą od zera.");
        return;
    }

    if (kwota > DodajSaldo::saldo) {
        ui->labelWyplacono->setText("Brak wystarczających środków w kaucji!");
        return;
    }

    if (ui->comboBoxBudzet->currentIndex() < 0 || ui->comboBoxKonto->currentIndex() < 0) {
        ui->labelWyplacono->setText("Wybierz budżet i konto docelowe.");
        return;
    }

    // Pobranie wskaźników na odpowiednie obiekty
    auto itBudzet = listaBudzetow->begin();
    std::advance(itBudzet, ui->comboBoxBudzet->currentIndex());

    // Sprawdzenie czy konto istnieje (zabezpieczenie)
    if ((size_t)ui->comboBoxKonto->currentIndex() >= itBudzet->konta.size()) return;

    auto itKonto = itBudzet->konta.begin();
    std::advance(itKonto, ui->comboBoxKonto->currentIndex());

    // LOGIKA BIZNESOWA:
    DodajSaldo::saldo -= kwota;      // Odejmij z kaucji
    itKonto->saldoZmiana(kwota);     // Dodaj do konta w budżecie

    // Informacja dla użytkownika
    ui->labelWyplacono->setText("Przelano " + QString::number(kwota, 'f', 2) + " zł na konto: " +
                                QString::fromStdString(itKonto->nazwaZwrot()));

    odswiezUI(); // Zaktualizuj wyświetlane saldo kaucji

    emit srodkiPrzelane();
}
