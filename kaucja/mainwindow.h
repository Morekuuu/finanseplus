#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Uzytkownik {
public:
    QString imie;
    double saldo, wyplaconeSrodki;
    Uzytkownik(QString i = "");
    QStringList historia;
    std::string budzet, konto;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonZatwierdzImie_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
