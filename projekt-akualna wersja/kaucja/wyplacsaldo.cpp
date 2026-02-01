#include "wyplacsaldo.h"
#include "dodajsaldo.h"
#include "ui_wyplacsaldo.h"
#include<QMessageBox>
#include <QShowEvent>

WyplacSaldo::WyplacSaldo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WyplacSaldo)
{
    ui->setupUi(this);
    ui->labelAktualneSaldo->setText(
        "Twoje aktualne saldo: " + QString::number(DodajSaldo::saldo) + " zł"
        );
}

WyplacSaldo::~WyplacSaldo()
{
    delete ui;
}

void WyplacSaldo::on_pushButtonZatwierdz_clicked()
{
    double kwota = ui->doubleSpinBox->value();
    if (kwota <= 0.0) {
        ui->labelWyplacono->setText("Podaj kwotę większą od 0.");
        return;

    }
    if (kwota > DodajSaldo::saldo) {
        ui->labelWyplacono->setText("Brak środków. Masz tylko: " +
                                    QString::number(DodajSaldo::saldo) + " zł.");
        return;
    }
    DodajSaldo::saldo -= kwota;

    ui->labelWyplacono->setText("Wypłacono: " + QString::number(kwota) +
                                " zł. Pozostało: " + QString::number(DodajSaldo::saldo) + " zł.");

    ui->labelAktualneSaldo->setText(
        "Twoje aktualne saldo: " + QString::number(DodajSaldo::saldo) + " zł"
        );
}



void WyplacSaldo::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    ui->labelAktualneSaldo->setText(
        "Twoje aktualne saldo: " + QString::number(DodajSaldo::saldo) + " zł"
        );
}
