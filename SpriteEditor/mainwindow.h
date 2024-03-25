#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "canvas.h"
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(model*, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void chooseColor();

public slots:
    //void onGridClicked(QPoint);
};
#endif // MAINWINDOW_H
