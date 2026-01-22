#ifndef DODAJSALDO_H
#define DODAJSALDO_H
#include"welcomewindow.h"
#include <QWidget>

class WelcomeWindow;

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
    explicit DodajSaldo(WelcomeWindow *welcome, QWidget *parent = nullptr);
    ~DodajSaldo();


private slots:
    void on_pushButtonZatwierdzKod_clicked();

    void on_pushButtonWroc_clicked();

private:
    Ui::DodajSaldo *ui;
    WelcomeWindow *welcomePtr;
};

#endif // DODAJSALDO_H
