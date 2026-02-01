#include "rejestracja.h"
#include "ui_rejestracja.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>

Rejestracja::Rejestracja(QWidget *parent)
    : QDialog(parent), ui(new Ui::Rejestracja) // Tu zmiana na duże R
{
    ui->setupUi(this);
    ui->haslo1->setEchoMode(QLineEdit::Password);
    ui->haslo2->setEchoMode(QLineEdit::Password);
}

Rejestracja::~Rejestracja(){
    delete ui;
}

QString Rejestracja::getLogin() const{
    return _login;
}

bool Rejestracja::hasloPoprawne(const QString &pass) const
{
    if(pass.length() < 8) return false;
    bool jestDuzaLitera = false;
    bool jestCyfra = false;
    for (int i = 0; i < pass.length(); i++) {
        QChar znak = pass[i];
        if (znak.isUpper()) jestDuzaLitera = true;
        if (znak.isDigit()) jestCyfra = true;
    }
    return jestDuzaLitera && jestCyfra;
}

QString Rejestracja::hashPassword(const QString &pass) const
{
    const QString salt = "abc123xyz";
    QString polaczone = salt + pass;
    QByteArray bajty = polaczone.toUtf8();
    QByteArray hashBinarne = QCryptographicHash::hash(bajty, QCryptographicHash::Sha256);
    return QString(hashBinarne.toHex());
}

void Rejestracja::on_stworz_konto_clicked()
{
    const QString login = ui->login->text().trimmed();
    const QString pass1 = ui->haslo1->text();
    const QString pass2 = ui->haslo2->text();

    if (login.isEmpty() || pass1.isEmpty() || pass2.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Uzupełnij wszystkie pola.");
        return;
    }
    if (pass1 != pass2) {
        QMessageBox::warning(this, "Błąd", "Hasła nie są takie same.");
        return;
    }
    if (!hasloPoprawne(pass1)) {
        QMessageBox::warning(this, "Błąd", "Hasło musi zawierać:\n- min. 8 znaków\n- 1 wielką literę\n- 1 cyfrę");
        return;
    }

    // Zapis do pliku
    QFile file("users.db");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString hash = hashPassword(pass1);
        out << login << ";" << hash << "\n";
        file.close();

        _login = login;
        QMessageBox::information(this, "Sukces", "Konto utworzone!");
        accept();
    } else {
        QMessageBox::critical(this, "Błąd", "Nie udało się zapisać do pliku.");
    }
}

void Rejestracja::on_pokaz_haslo1_clicked()
{
    if (ui->haslo1->echoMode() == QLineEdit::Password)
        ui->haslo1->setEchoMode(QLineEdit::Normal);
    else
        ui->haslo1->setEchoMode(QLineEdit::Password);
}

void Rejestracja::on_pokaz_haslo2_clicked()
{
    if (ui->haslo2->echoMode() == QLineEdit::Password)
        ui->haslo2->setEchoMode(QLineEdit::Normal);
    else
        ui->haslo2->setEchoMode(QLineEdit::Password);
}
