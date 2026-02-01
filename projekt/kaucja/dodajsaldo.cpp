#include "dodajsaldo.h"
#include "ui_dodajsaldo.h"
#include<QString>
#include<unordered_map>
#include"wrzucbutelki.h"



DodajSaldo::DodajSaldo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DodajSaldo)

{
    ui->setupUi(this);
}

DodajSaldo::~DodajSaldo()
{
    delete ui;
}

void DodajSaldo::on_pushButtonZatwierdzKod_clicked()
{
    QString kodWpisany = ui->lineEditWpiszKod->text().trimmed();
    std::string kod = kodWpisany.toStdString();
    auto it = WrzucButelki::bazaKodow.find(kod);

    if(it != WrzucButelki::bazaKodow.end()) {
        double kwota = it->second;                            //first to kod second to wartosc
        ui->labelWiadomoscZwrotna->setText("Kod zrealizowano pomyślnie! Dodano " + QString::number(kwota) + " zł do salda.");
        WrzucButelki::bazaKodow.erase(it);
        QString wpis = QString("+" + QString::number(kwota) + " zł");
    } else {
        ui->labelWiadomoscZwrotna->setText("Nie znaleziono kodu.");
    }
}




void DodajSaldo::on_pushButtonWroc_clicked()
{
    this->close();
}

