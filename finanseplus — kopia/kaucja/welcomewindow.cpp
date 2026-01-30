#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "wrzucbutelki.h"
#include"dodajsaldo.h"
#include"wyplacsaldo.h"

WelcomeWindow::WelcomeWindow(Uzytkownik *user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeWindow)
    , userPtr(user)
{
    ui->setupUi(this);
    ui->labelWelcome->setText("Witaj, " + userPtr->imie + "!");
    this->setWindowTitle("Witaj w aplikacji kaucyjnej!");
    ui->labelSaldo->setText(QString::number(userPtr->saldo) + "zł");

}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_pushButtonDodajSaldo_clicked()
{
    DodajSaldo *saldo = new DodajSaldo(this);
    saldo -> show();
}


void WelcomeWindow::on_pushButtonWrzucButelki_clicked()
{
    WrzucButelki *wrzuc = new WrzucButelki();
    wrzuc -> show();
}

void WelcomeWindow::aktualizujSaldo() {
    ui->labelSaldo->setText(QString::number(userPtr->saldo) + "zł");
}


void WelcomeWindow::on_pushButtonWyplacSaldo_clicked()
{
    WyplacSaldo *wyplac = new WyplacSaldo(userPtr, this);
    wyplac->show();
}

void WelcomeWindow::aktualizujHistorie() {
    ui->listWidgetHistoria->clear();
    ui->listWidgetHistoria->addItems(userPtr->historia);
}

