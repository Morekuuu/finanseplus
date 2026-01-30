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

//hashowanie hasła
static QString hashPassword(const QString &pass)
{

    const QString salt = "abc123xyz";
    QByteArray data = (salt + pass).toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    return hash.toHex();
}


//logowanie
void Logowanie::on_zaloguj_clicked()
{
    QString login = ui->login->text();
    QString pass  = ui->haslo->text();
    QString passHash = hashPassword(pass);
    QString correctHash = "5208d4270baced7070ccfc4948731b34cf8f3fa697398a0fa6b423a48dfa81b8";

    //poprawne dane
    if (login == "login" && passHash == correctHash)
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
