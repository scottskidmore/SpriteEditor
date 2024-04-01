#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "qtimer.h"
#include <QColorDialog>
#include <QMessageBox>

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
    int currentFrame=0;
    std::vector<QImage> frames;
    int frameTime=67;
    ///
    /// \brief chooseColor displays a popup of color choices then sets pen color to chosen color.
    ///
    void chooseColor();

signals:
    void frameButtonAdded();
    void frameButtonRemoved();
    void createNewSprite();

public slots:
    //void onGridClicked(QPoint);
    ///
    /// \brief onAddFrame
    ///
    void onAddFrame();
    void updateFrameDisplay(std::vector<QImage> images);
    void storeFrames(std::vector<QImage> images);
    void connectButtonFrame();
    void connectNewFrame();
    void onRemoveFrame();
    void animate();
    void onNewButtonPressed();
    void loadPressed();
    void updateFps(int i);
    void helpClicked();
    void changeUsingLayerText(QString text);
    void saveDialog();
    void changeToLoadSize(int size);
};
#endif // MAINWINDOW_H
