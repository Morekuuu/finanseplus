#include "rejestracja.h"
#include "ui_rejestracja.h"

#include <QMessageBox>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QLineEdit>

//tworzy ui
Rejestracja::Rejestracja(QWidget *parent)
    : QDialog(parent), ui(new Ui::rejestracja)
{
    ui->setupUi(this);
    ui->haslo1->setEchoMode(QLineEdit::Password);
    ui->haslo2->setEchoMode(QLineEdit::Password);
}

//destruktor ui
Rejestracja::~Rejestracja(){
    delete ui;
}

//dostep do loginu i hasła
QString Rejestracja::getLogin() const{
    return _login;
}
QString Rejestracja::getHash()  const{
    return _hash;
}

//sprawdza warunki(min.8 znakow, wielka litera, cyfra)
bool Rejestracja::hasloPoprawne(const QString &pass) const
{
    if(pass.length()<8)return false;
    bool jestDuzaLitera = false;
    bool jestCyfra = false;
    for (int i = 0; i < pass.length(); i++) {
        QChar znak = pass[i];

        //czy jest duza litera(znak.isUpper sprawia ze program widz tez znaki  polski Ą,Ę,Ł itp.)
        if (znak.isUpper())
            jestDuzaLitera = true;

        // czy jest cyfra
        if (znak.isDigit())
            jestCyfra = true;
    }

    //brak duzej litery
    if (!jestDuzaLitera)
        return false;

    //brak cyfry
    if (!jestCyfra)
        return false;
    return true;
}

//hashowanie hasla
QString Rejestracja::hashPassword(const QString &pass) const
{
    //dodajemy salt do hasla zeby hash byl trudiejszy do złamania
    const QString salt = "abc123xyz";
    //laczy salt+pass
    QString polaczone = salt + pass;
    QByteArray bajty = polaczone.toUtf8();// to.Utf8 zamienia tekts(salt+pass) na bajty)
    QByteArray hashBinarne = QCryptographicHash::hash(bajty, QCryptographicHash::Sha256);//tworzy hash(256 bitow)
    QByteArray hashHex = hashBinarne.toHex();// zamienia hash na(64 "losowe" znaki)
    return QString(hashHex);//zwraca juz gotowy hash

}

void Rejestracja::on_stworz_konto_clicked()
{
    //pobiera wpisane dane z pól
    const QString login = ui->login->text().trimmed();  //.trimmed usuwa spacje z poaczątku lub konca jesli takie wystepują
    const QString pass1 = ui->haslo1->text();
    const QString pass2 = ui->haslo2->text();

    //jesli wszytkie nie sa zapisane
    if (login.isEmpty() || pass1.isEmpty() || pass2.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Uzupełnij wszystkie pola.");
        return;
    }
    //jesli haslo 1 i halo 2 nie sa identyczne
    if (pass1 != pass2) {
        QMessageBox::warning(this, "Błąd", "Hasła nie są takie same.");
        return;
    }
    // jesli haslo nie spelnia warunków
    if (!hasloPoprawne(pass1)) {
        QMessageBox::warning(this, "Błąd",
                             "Hasło musi zawierać:\n- min. 8 znaków\n- 1 wielką literę\n- 1 cyfrę");
        return;
    }

    //jesli wszytko zgodne z założeniami przypisujemy wpisane dane loginu i hasła(hasło w formie hashu)
    _login = login;
    _hash  = hashPassword(pass1);

    accept(); // przejście do logowania
}

void Rejestracja::on_pokaz_haslo1_clicked()
{
    if (ui->haslo1->echoMode() == QLineEdit::Password)
    {
        ui->haslo1->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->haslo1->setEchoMode(QLineEdit::Password);
    }
}

void Rejestracja::on_pokaz_haslo2_clicked()
{
    if (ui->haslo2->echoMode() == QLineEdit::Password)
    {
        ui->haslo2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->haslo2->setEchoMode(QLineEdit::Password);
    }
}
