#ifndef LOGOWANIE_H
#define LOGOWANIE_H
#include <QDialog>

namespace Ui {
class Logowanie;
}

class Logowanie : public QDialog
{
    Q_OBJECT

public:
    explicit Logowanie(QWidget *parent = nullptr);
    ~Logowanie();
    void setKonto(const QString &login, const QString &hash);
private slots:
    void on_zaloguj_clicked();      //logowanie
    void on_pokazHaslo_clicked();   //pokaz/ukryj haslo
private:
    Ui::Logowanie *ui; //wskazniki do ui

    QString _login;
    QString _hash;

    //haslowanie wpisanego hasla aby porownac z tym z rejestracji
    QString hashPassword(const QString &pass)const;

};

#endif // LOGOWANIE_H
