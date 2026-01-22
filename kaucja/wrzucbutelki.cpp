#include "wrzucbutelki.h"
#include "ui_wrzucbutelki.h"
#include<QDebug>
#include "welcomewindow.h"
#include<string>
#include<cstdlib>
#include<ctime>
#include<QClipboard>
#include<unordered_map>

std::unordered_map<std::string, double> WrzucButelki::bazaKodow;

WrzucButelki::WrzucButelki(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WrzucButelki)
{
    ui->setupUi(this);
    //connect(ui->pushButtonZatwierdzButelki, &QPushButton::clicked, this, &WrzucButelki::on_pushButtonZatwierdzButelki_clicked);
    ui->pushButtonKopiujKod->setVisible(false);
}

WrzucButelki::~WrzucButelki()
{
    delete ui;
}

std::string LosujButelki::wylosujKod() {
    srand(time(0));

    std::string znakow = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string losowyCiag;
    for(int i = 0; i < 10; i++) {
        int losowyIndex = rand() % znakow.length();
        losowyCiag += znakow[losowyIndex];
    }
    return losowyCiag;
}



void WrzucButelki::on_pushButtonZatwierdzButelki_clicked()
{
    LosujButelki l1;
    int puszki = ui -> spinBoxPuszki->value();
    int plastikowe = ui -> spinBoxPlastikowe->value();
    int szklane = ui -> spinBoxSzklane->value();
    double kwotaZaKod = 0.5*puszki + 0.5*plastikowe + 1.0*szklane;
    std::string kod = l1.wylosujKod();
    WrzucButelki::bazaKodow[kod] = kwotaZaKod;
    ui ->labelZwrocKwote->setText("Twój kod na wartość: " + QString::number(kwotaZaKod) + "zł to: ");
    ui ->labelZwrocKod->setText(QString::fromStdString(kod));
    ui ->labelZwrocKod->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->pushButtonKopiujKod->setVisible(true);
    ui ->listWidgetHistoria ->addItem(QString::fromStdString(kod) + "   :   " + QString::number(kwotaZaKod) + "zł");

}


void WrzucButelki::on_pushButtonKopiujKod_clicked()
{
    QString kod = ui->labelZwrocKod->text();
    QApplication::clipboard() -> setText(kod);
}


void WrzucButelki::on_pushButtonWroc_clicked()
{
    this -> close();
}

