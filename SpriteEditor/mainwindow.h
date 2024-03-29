#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "qtimer.h"
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
    QTimer timer;
    Ui::MainWindow *ui;
    model* m;
    void chooseColor();
    int currentFrame=0;
    std::vector<QImage> frames;

signals:
    void frameButtonAdded();
    void frameButtonRemoved();
    void createNewSprite();

public slots:
    //void onGridClicked(QPoint);
    void onAddFrame();
    void updateFrameDisplay(std::vector<QImage> images);
    void storeFrames(std::vector<QImage> images);
    void connectButtonFrame();
    void connectNewFrame();
    void onRemoveFrame();
    void animate();
    void onNewButtonPressed();
};
#endif // MAINWINDOW_H
