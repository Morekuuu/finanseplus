#include "logowanie.h"
#include "ui_logowanie.h"
#include "mainwindow.h"
#include <QMessageBox>

Logowanie::Logowanie(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Logowanie)
{
    ui->setupUi(this);
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_zaloguj_clicked()
{
    QString login = ui->login->text();
    QString pass  = ui->haslo->text();

    if (login == "login" && pass == "hasło")
    {
        MainWindow *m = new MainWindow();
        m->show();
        close();
    }
    else
    {
        QMessageBox::warning(this, "Błąd", "Niepoprawny login lub hasło!");
        ui->login->clear();
        ui->haslo->clear();
    }
}
void Logowanie::on_pokazHaslo_clicked()
{
    if (ui->haslo->echoMode() == QLineEdit::Password)
    {
        ui->haslo->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->haslo->setEchoMode(QLineEdit::Password);
    }
}
