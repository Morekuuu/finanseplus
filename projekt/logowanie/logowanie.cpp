#include "logowanie.h"
#include "ui_logowanie.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>

//tworzy pola i przyciski
Logowanie::Logowanie(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Logowanie)
{
    ui->setupUi(this);
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::setKonto(const QString &login, const QString &hash)
{
    //przekazuje dane z rejestracji
    _login = login;
    _hash  = hash;

}

    //hashowanie hasla
QString Logowanie::hashPassword(const QString &pass)const
{
    //dodajemy salt do hasla zeby hash byl trudiejszy do złamania (salt musi być takie samo jak w rejestracji)
    const QString salt = "abc123xyz";
    //laczy salt+pass
    QString polaczone = salt + pass;
    QByteArray bajty = polaczone.toUtf8();// to.Utf8 zamienia tekts(salt+pass) na bajty)
    QByteArray hashBinarne = QCryptographicHash::hash(bajty, QCryptographicHash::Sha256);//tworzy hash(256 bitow)
    QByteArray hashHex = hashBinarne.toHex();// zamienia hash na(64 "losowe" znaki)
    return QString(hashHex);//zwraca juz gotowy hash

}


//logowanie
void Logowanie::on_zaloguj_clicked()
{
    QString login = ui->login->text();
    QString pass  = ui->haslo->text();
    QString passHash = hashPassword(pass);

    //poprawne dane(porownuje login i haslo z tymi z rejestracji)
    if (login == _login && passHash == _hash)
    {
        accept();
    }

    //błedne dane
    else
    {
        QMessageBox::warning(this, "Błąd", "Niepoprawny login lub hasło!");
        ui->login->clear();
        ui->haslo->clear();
    }
}

//pokaż/ukryj hasło
void Logowanie::on_pokazHaslo_clicked()
{
    if (ui->haslo->echoMode() == QLineEdit::Password)
    {
        ui->haslo->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->haslo->setEchoMode(QLineEdit::Password);
    }
}
