#pragma once
#include <QDialog>

namespace Ui { class Rejestracja; }

class Rejestracja : public QDialog
{
    Q_OBJECT
public:
    explicit Rejestracja(QWidget *parent = nullptr);
    ~Rejestracja();

    QString getLogin() const;

private slots:
    void on_stworz_konto_clicked();
    void on_pokaz_haslo1_clicked();
    void on_pokaz_haslo2_clicked();

private:
    Ui::Rejestracja *ui;

    QString _login;
    QString _hash;

    bool hasloPoprawne(const QString &pass) const;
    QString hashPassword(const QString &pass) const;
};
