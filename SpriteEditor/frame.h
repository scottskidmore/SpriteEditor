#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include "qobject.h"
#include <vector>

/// \brief The Frame class - a class for storing and updating individual frames
/// Inherits from QObject
class Frame : public QObject
{
    Q_OBJECT
public:
    /// \brief Frame constructor
    /// \param parent QObject defaulted to nullptr
    explicit Frame(QObject *parent = nullptr);
    /// \brief drawPixel draws a pixel on the current frame at the point
    /// \param QPoint point to draw at
    void drawPixel(QPoint);
    /// \brief getCurrentLayer getter for the current layer in the frame
    /// \return QImage& layer
    QImage& getCurrentLayer();
    /// \brief frameID stored identifier for a frame
    int frameID;
    /// \brief images vector of QImages representing the layers
    std::vector<QImage> images;
    /// \brief setCurrentLayer setter for the current layer
    /// \param int layer number
    void setCurrentLayer(int);
    /// \brief imageSize size of the image eg. 16x16, 32x32, 64x64
    int imageSize;
    /// \brief currentImage current layer number
    int currentImage;

signals:
    /// \brief updateImage emitted to update the frames
    /// \param vector<QImage> vector of layers
    void updateImage(std::vector<QImage>);
    /// \brief changeFrame emitted to change the current frame
    /// \param id of frame to change to
    void changeFrame(int id);

public slots:
    /// \brief sendImages sends the layers to the UI
    void sendImages();
    /// \brief frameButtonPressed changes the current frame to the frame clicked on UI
    void frameButtonPressed();
    /// \brief updateImageSize16 clears the layers and sets the size to 16x16
    void updateImageSize16();
    /// \brief updateImageSize32 clears the layers and sets the size to 32x32
    void updateImageSize32();
    /// \brief updateImageSize64 clears the layers and sets the size to 64x64
    void updateImageSize64();

};

#endif // FRAME_H
