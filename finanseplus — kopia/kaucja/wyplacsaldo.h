#ifndef WYPLACSALDO_H
#define WYPLACSALDO_H
#include <QWidget>

namespace Ui {
class WyplacSaldo;
}

class WyplacSaldo : public QWidget
{
    Q_OBJECT

public:
    explicit WyplacSaldo(QWidget *parent = nullptr);
    ~WyplacSaldo();


private slots:
    void on_pushButtonZatwierdz_clicked();

    void on_pushButtonWroc_clicked();

private:
    Ui::WyplacSaldo *ui;
};

#endif // WYPLACSALDO_H
