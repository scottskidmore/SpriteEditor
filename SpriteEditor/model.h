#ifndef MODEL_H
#define MODEL_H

#include "draw.h"
#include "animation.h"
#include "qobject.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QPushButton>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:

    explicit Model(QObject *parent = nullptr);
    Draw pen;
    Animation a;
    Frame* f;
    ///
    /// \brief setDrawLayer - sets the draw layer for the pen to the current layer that the frame has stored.
    ///
    void setDrawLayer();
    ///
    /// \brief loadPressed - loads a .ssp file to the sprite editor from the file param
    /// \param file - filepath for where to get the file from
    ///
    void loadPressed(QString file);
    ///
    /// \brief getFrameCount - returns the number of frames this Model/animation has.
    /// \return number of frames
    ///
    int getFrameCount();


private:
    enum tools {Pen, Eraser, Square, Circle, SprayCan};
    tools currentTool;
    ///
    /// \brief getFrameImages - condenses the frame layers into one image and emits updateFrameDisplay signal
    /// helps so the buttons to switch frames have their content displayed.
    ///
    void getFrameImages();

signals:
    ///
    /// \brief connectFrameButton - emits when a new frame has been created and can be connected to a button on the view
    ///
    void connectFrameButton();
    ///
    /// \brief connectFrameUpdate - emits when a frame is switched or when the frames are cleared
    ///
    void connectFrameUpdate();
    ///
    /// \brief updateFrameDisplay - emits to change the Frame selection bar icons
    /// \param images - images of each frame
    ///
    void updateFrameDisplay(std::vector<QImage> images);
    ///
    /// \brief swapLayerText - when a layer is changed this is emitted to change the main window text
    /// \param text - the text that will be displayed
    ///
    void swapLayerText(QString text);
    ///
    /// \brief updateLoadImageSize - emits when loading from a file to change the canvas size
    /// \param size - 16, 32, or 64 depending on the file
    ///
    void updateLoadImageSize(int size);
    ///
    /// \brief clearAnimation - lets the animation know to clear
    ///
    void clearAnimation();
    ///
    /// \brief loadFps - emits when loading a file to change fps
    /// \param fps
    ///
    void loadFps(int fps);


public slots:
    ///
    /// \brief editImage - calls the pen draw methods accordingly, and will tell the frame to emit its images.
    ///  also emits images for frame icons at the bottom of the canvas.
    ///
    void editImage(QPoint);
    ///
    /// \brief handleDrawingShapes - handles drawing shapes when a shape tool is selected
    /// dragging your mouse will draw different size shapes when holding click.
    ///
    void handleDrawingShapes(QPoint, QPoint);

    ///
    /// \brief erasePressed, drawPressed, circlePressed, squarePressed, sprayCanPressed - All switch the field currentTool to the appropriate tool.
    ///
    void erasePressed();
    void drawPressed();
    void circlePressed();
    void squarePressed();
    void sprayCanPressed();

    ///
    /// \brief savePressed - saves the current sprite to the designated path in json.
    ///
    void savePressed(QString path);
    ///
    /// \brief addFrame - adds a frame and emits the connectFrameButton signal so it can be connected to a button
    ///
    void addFrame();
    ///
    /// \brief switchFrame - called when a frame button is pressed so the frame being edited can be switched.
    /// \param id - an ID with index 0 to start. ID is its place in the animation array of images
    ///
    void switchFrame(int id);
    ///
    /// \brief deleteFrame - removes the most recently added frame.
    ///
    void deleteFrame();

    ///
    /// \brief layer1, layer2, layer3, layer4, layer5 - all switch to the appropriate layer and emit swapLayerText signal
    ///
    void layer1();
    void layer2();
    void layer3();
    void layer4();
    void layer5();

    ///
    /// \brief clearAll - clears all frames from this model and adds a new blank starting frame 32x32
    ///
    void clearAll();
    ///
    /// \brief updateAllFrameSizes - changes all frames to the new size that is pressed.
    ///
    void updateAllFrameSizes();
    ///
    /// \brief updateFrameSizeInt - changes the frames size that is passed in
    /// \param size - 16, 32, or 64
    /// \param frame - pointer to a frame which size will be changed
    ///
    void updateFrameSizeInt(int size, Frame* frame);
    ///
    /// \brief updateFrameRate - changes this models frame rate to the passed in int
    ///
    void updateFrameRate(int);
};

#endif // MODEL_H
