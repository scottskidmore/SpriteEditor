#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    model *m = new model();
    MainWindow w(m);
    w.show();
    return a.exec();
}
