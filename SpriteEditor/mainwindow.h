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
    model* m;
    void chooseColor();

signals:
    void frameButtonAdded();
    void frameButtonRemoved();

public slots:
    //void onGridClicked(QPoint);
    void onAddFrame();
    void updateFrameDisplay(std::vector<QImage> images);
    void connectButtonFrame();
    void connectNewFrame();
    void onRemoveFrame();
};
#endif // MAINWINDOW_H
