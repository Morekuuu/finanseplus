#ifndef WRZUCBUTELKI_H
#define WRZUCBUTELKI_H
#include <iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<unordered_map>


#include <QWidget>

namespace Ui {
class WrzucButelki;
}

class LosujButelki {
    public:
    std::string wylosujKod();
    void dodajKod(double kwota);
};

class WrzucButelki : public QWidget
{
    Q_OBJECT

public:
    explicit WrzucButelki(QWidget *parent = nullptr);
    ~WrzucButelki();
    static std::unordered_map<std::string, double> bazaKodow;


private slots:
    void on_pushButtonZatwierdzButelki_clicked();

    void on_pushButtonKopiujKod_clicked();

    void on_pushButtonWroc_clicked();

private:
    Ui::WrzucButelki *ui;
};

#endif // WRZUCBUTELKI_H
