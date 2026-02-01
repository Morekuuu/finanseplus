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
    void on_zaloguj_clicked();
    void on_pokazHaslo_clicked();

    void on_btnRejestracja_clicked();

private:
    Ui::Logowanie *ui;

    bool sprawdzWPliku(const QString &login, const QString &hash);
    QString hashPassword(const QString &pass) const;
};

#endif
