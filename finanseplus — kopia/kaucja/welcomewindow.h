#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H
#include"mainwindow.h"
#include <QWidget>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(Uzytkownik *user, QWidget *parent = nullptr);
    ~WelcomeWindow();
    Uzytkownik *userPtr;
    void aktualizujSaldo();
    void aktualizujHistorie();


private slots:
    void on_pushButtonDodajSaldo_clicked();

    void on_pushButtonWrzucButelki_clicked();

    void on_pushButtonWyplacSaldo_clicked();

private:
    Ui::WelcomeWindow *ui;
};

#endif // WELCOMEWINDOW_H
