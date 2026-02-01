#ifndef DODAJSALDO_H
#define DODAJSALDO_H

#include <QWidget>
#include <string>



namespace Ui {
class DodajSaldo;
}


class UzyjKod {
    public:
    bool wykorzystajKod(const std::string& kod, double& wartosc);
};

class DodajSaldo : public QWidget
{
    Q_OBJECT

public:
    explicit DodajSaldo( QWidget *parent = nullptr);
    ~DodajSaldo();


private slots:
    void on_pushButtonZatwierdzKod_clicked();

    void on_pushButtonWroc_clicked();

private:
    Ui::DodajSaldo *ui;
};

#endif // DODAJSALDO_H
