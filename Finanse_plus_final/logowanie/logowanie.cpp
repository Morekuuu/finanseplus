#include "logowanie.h"
#include "ui_logowanie.h"
#include "rejestracja.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>

Logowanie::Logowanie(QWidget *parent) : QDialog(parent), ui(new Ui::Logowanie)
{
    ui->setupUi(this);
}

Logowanie::~Logowanie()
{
    delete ui;
}

QString Logowanie::hashPassword(const QString &pass) const
{
    const QString salt = "abc123xyz";
    QString polaczone = salt + pass;
    return QString(QCryptographicHash::hash(polaczone.toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool Logowanie::sprawdzWPliku(const QString &wpisanyLogin, const QString &wpisanyHash)
{
    QFile file("users.db");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(";");
        if (fields.size() >= 2) {
            if (fields[0] == wpisanyLogin && fields[1] == wpisanyHash) return true;
        }
    }
    return false;
}

void Logowanie::on_zaloguj_clicked()
{
    QString login = ui->login->text().trimmed();
    QString pass  = ui->haslo->text();

    if (sprawdzWPliku(login, hashPassword(pass))) {
        accept();
    } else {
        QMessageBox::warning(this, "Błąd", "Błędne dane!");
    }
}

void Logowanie::on_pokazHaslo_clicked()
{
    ui->haslo->setEchoMode(ui->haslo->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password);
}

void Logowanie::on_btnRejestracja_clicked()
{
    Rejestracja okno(this);
    okno.exec();
}
