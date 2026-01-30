#include "logowanie.h"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //jesli dobre logowanie tworzy maina
    QApplication a(argc, argv);
    Logowanie dlg;
    if(dlg.exec()==QDialog::Accepted){
        MainWindow w;
        w.show();

        return a.exec();
    }
    return 0;
}
