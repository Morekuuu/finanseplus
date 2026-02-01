#include "mainwindow.h"
#include "logowanie.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logowanie l;

    if (l.exec() == QDialog::Accepted) {

        MainWindow w;
        w.show();

        return a.exec();
    }

    return 0;
}
