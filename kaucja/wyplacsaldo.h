#ifndef WYPLACSALDO_H
#define WYPLACSALDO_H
#include"mainwindow.h"
#include"welcomewindow.h"
#include <QWidget>

namespace Ui {
class WyplacSaldo;
}

class WyplacSaldo : public QWidget
{
    Q_OBJECT

public:
    explicit WyplacSaldo(Uzytkownik *user, WelcomeWindow *welcome ,QWidget *parent = nullptr);
    ~WyplacSaldo();
    Uzytkownik *userPtr;
    WelcomeWindow *welcomePtr;

private slots:
    void on_pushButtonZatwierdz_clicked();

    void on_pushButtonWroc_clicked();

private:
    Ui::WyplacSaldo *ui;
};

#endif // WYPLACSALDO_H
