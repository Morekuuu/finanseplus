#ifndef WYPLACSALDO_H
#define WYPLACSALDO_H

#include <QWidget>
#include <list>          // Ważne: dla std::list
#include <QComboBox>     // Ważne: naprawia błąd "'QComboBox' has not been declared"
#include "../budzet/budzet.h"

namespace Ui {
class WyplacSaldo;
}

class WyplacSaldo : public QWidget
{
    Q_OBJECT

public:
    // Konstruktor przyjmuje wskaźnik na listę budżetów
    explicit WyplacSaldo(std::list<Budzet> *lista, QWidget *parent = nullptr);
    ~WyplacSaldo();

signals:
    void srodkiPrzelane();

private slots:
    void on_pushButtonZatwierdz_clicked();
    void on_comboBoxBudzet_currentIndexChanged(int index);

private:
    Ui::WyplacSaldo *ui;
    std::list<Budzet> *listaBudzetow;

    void showEvent(QShowEvent* event) override;
    void odswiezUI();
};

#endif // WYPLACSALDO_H
