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

class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = nullptr);
    //model();
    Draw pen;
    Animation a;
    Frame* f;
    void setDrawLayer();
    void loadPressed(QString file);
    ///
    /// \brief getFrameCount - returns the number of frames this model/animation has.
    /// \return number of frames
    ///
    int getFrameCount();


private:
    //char currentTool;
    enum tools {Pen, Eraser, Square, Circle, SprayCan};
    tools currentTool;
    ///
    /// \brief getFrameImages - condenses the frame layers into one image and emits updateFrameDisplay signal
    /// helps so the buttons to switch frames have their content displayed.
    ///
    void getFrameImages();

signals:
    void connectFrameButton();
    void connectFrameUpdate();
    void updateFrameDisplay(std::vector<QImage> images);
    void swapLayerText(QString text);
    void updateLoadImageSize(int size);


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
    /// \param id
    ///
    void switchFrame(int id);
    ///
    /// \brief deleteFrame
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
    /// \brief clearAll
    ///
    void clearAll();
    ///
    /// \brief updateAllFrameSizes
    ///
    void updateAllFrameSizes();
    void updateFrameSizeInt(int size, Frame* frame);
    ///
    /// \brief updateFrameRate
    ///
    void updateFrameRate(int);
};

#endif // MODEL_H
