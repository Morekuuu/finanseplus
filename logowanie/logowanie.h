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

private slots:
    void on_zaloguj_clicked();      //logowanie
    void on_pokazHaslo_clicked();   //pokaz/ukryj haslo
private:
    Ui::Logowanie *ui; //wskazniki do ui
};

#endif // LOGOWANIE_H
