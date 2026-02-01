#include "logowanie.h"
#include <QApplication>
#include "mainwindow.h"
#include "rejestracja.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Rejestracja r;
    if (r.exec() != QDialog::Accepted)
        return 0;

    Logowanie l;
    //pobiera login i hash z rejestracji
    l.setKonto(r.getLogin(), r.getHash());
    //jesli dobre logowanie tworzy maina
    if(l.exec()==QDialog::Accepted){
        MainWindow w;
        w.show();

        return a.exec();
    }
    return 0;
}
