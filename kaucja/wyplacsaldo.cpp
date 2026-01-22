#include "wyplacsaldo.h"
#include "ui_wyplacsaldo.h"
#include<QMessageBox>

WyplacSaldo::WyplacSaldo(Uzytkownik *user, WelcomeWindow *welcome ,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WyplacSaldo)
    , userPtr(user)
    , welcomePtr(welcome)
{
    ui->setupUi(this);
    ui->labelAktualneSaldo->setText("Twoje aktualne saldo: " + QString::number(userPtr->saldo) + " zł");
}

WyplacSaldo::~WyplacSaldo()
{
    delete ui;
}

void WyplacSaldo::on_pushButtonZatwierdz_clicked()
{
    double kwota = ui->doubleSpinBox->value();

    if(kwota > userPtr->saldo) {
        ui->labelWyplacono->setText("Kwota którą chcesz wypłacić jest większa od stanu twojego konta. Saldo nie zostało obciążone");
    } else {
        userPtr->wyplaconeSrodki+=kwota;
        userPtr->saldo-=kwota;
        ui->labelAktualneSaldo->setText("Twoje aktualne saldo: " + QString::number(userPtr->saldo) + " zł");
        ui->labelWyplacono->setText("Pomyślnie wypłacono " + QString::number(kwota) + " zł z twojego konta. Saldo zostało zaktualizowane");
        welcomePtr->aktualizujSaldo();
        qDebug() << "Wyplacone srodki: " << userPtr->wyplaconeSrodki;
        QString wpis = QString("-" + QString::number(kwota) + " zł, Saldo = " + QString::number(welcomePtr->userPtr->saldo) + "zł");
        userPtr->historia.prepend(wpis);
        welcomePtr->aktualizujHistorie();

        std::string konto = ui->labelKonto->text().trimmed().toStdString();
        std::string budzet = ui->labelBudzet->text().trimmed().toStdString();
        userPtr->budzet = budzet;
        userPtr->konto = konto;
    }
}


void WyplacSaldo::on_pushButtonWroc_clicked()
{
    this->close();
}

