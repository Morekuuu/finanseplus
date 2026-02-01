#pragma once
#include <QDialog>

namespace Ui { class rejestracja; }

class Rejestracja : public QDialog
{
    Q_OBJECT
public:
    explicit Rejestracja(QWidget *parent = nullptr);
    ~Rejestracja();

    //przekazanie loginu i hasła
    QString getLogin() const;
    QString getHash() const;

private slots:
    //przyciski
    void on_stworz_konto_clicked();
    void on_pokaz_haslo1_clicked();
    void on_pokaz_haslo2_clicked();

private:
    Ui::rejestracja *ui;

    //zmienne
    QString _login;
    QString _hash;

    //sprawdzenie hasła +hash
    bool hasloPoprawne(const QString &pass) const;
    QString hashPassword(const QString &pass) const;
};
