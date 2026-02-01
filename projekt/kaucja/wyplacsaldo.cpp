#include "wyplacsaldo.h"
#include "ui_wyplacsaldo.h"
#include<QMessageBox>

WyplacSaldo::WyplacSaldo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WyplacSaldo)
{
    ui->setupUi(this);
    ui->labelAktualneSaldo->setText("Twoje aktualne saldo: zł");
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
}

void WyplacSaldo::on_pushButtonWroc_clicked()
{
    this->close();
}

