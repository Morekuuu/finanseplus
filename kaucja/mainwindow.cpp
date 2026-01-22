#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QDebug>
#include "welcomewindow.h"
#include <QMessageBox>

Uzytkownik::Uzytkownik(QString i) {
    imie = i;
    saldo = 0.0;
    wyplaconeSrodki = 0.0;
    budzet = "";
    konto = "";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonZatwierdzImie_clicked()
{
    QString imie = ui->lineEditName->text().trimmed();
    qDebug() << "Użytkownik wpisał: " << imie;
    if(imie.isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Podaj swoje imię!");
        return;
    }

    Uzytkownik *user = new Uzytkownik(imie);

    WelcomeWindow *welcome = new WelcomeWindow(user);
    welcome->show();
    this -> close();
}

