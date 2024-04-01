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
    MainWindow(Model*, QWidget *parent = nullptr);
    ~MainWindow();


private:
    QTimer timer;
    Ui::MainWindow *ui;
    Model* m;
    void chooseColor();
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
    /// \brief onAddFrame adds a new frame button to the ui.
    ///
    void onAddFrame();
    ///
    /// \brief updateFrameDisplay updates frame display for each image in the image collection.
    /// \param images the collection of images to display.
    ///
    void updateFrameDisplay(std::vector<QImage> images);
    ///
    /// \brief storeFrames
    /// \param images
    ///
    void storeFrames(std::vector<QImage> images);
    ///
    /// \brief connectButtonFrame connects frame buttons.
    ///
    void connectButtonFrame();
    ///
    /// \brief connectNewFrame connects new frames to the canvas.
    ///
    void connectNewFrame();
    ///
    /// \brief onRemoveFrame handles removing a frame when remove frame is clicked.
    ///
    void onRemoveFrame();
    ///
    /// \brief animate uses a timer to cycle through multiple frames.
    ///
    void animate();
    ///
    /// \brief onNewButtonPressed handles the creation of a new sprite when new is clicked.
    ///
    void onNewButtonPressed();
    ///
    /// \brief loadPressed handles loading of sprite files ending in .ssp.
    ///
    void loadPressed();
    ///
    /// \brief updateFps updates fps.
    /// \param i value from the scroll bar.
    ///
    void updateFps(int i);
    ///
    /// \brief helpClicked displays help text when help button is clicked.
    ///
    void helpClicked();
    ///
    /// \brief changeUsingLayerText changes the layer text to new text.
    /// \param text the text to set the layer text to.
    ///
    void changeUsingLayerText(QString text);
    ///
    /// \brief saveDialog
    ///
    void saveDialog();
    ///
    /// \brief changeToLoadSize changes canvas size to what the loaded file's size is.
    /// \param size new canvas size.
    ///
    void changeToLoadSize(int size);
};
#endif // MAINWINDOW_H
