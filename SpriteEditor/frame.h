#ifndef FRAME_H
#define FRAME_H
#include <QImage>
#include "qobject.h"
#include <vector>
//Drew Humphrey

/// \brief The Frame class - handles the individual frames of the animation
/// Inherits from QObject
class Frame : public QObject
{
    Q_OBJECT
public:

    QImage& getCurrentLayer();
    int frameID;
    std::vector<QImage> images;

    /// \brief Frame constructor
    /// \param parent QObject defaulted to nullptr
    explicit Frame(QObject *parent = nullptr);

    /// \brief drawPixel draws pixel at location stored by QPoint on the current image.
    /// \param QPoint where to draw the pixel
    void drawPixel(QPoint);

    /// \brief setCurrentLayer sets current layer to layer at specified index of layer collection.
    /// \param int i the index of the layer to switch to.
    void setCurrentLayer(int);
    int imageSize;
    int currentImage;

signals:

    /// \brief Send signal to update image
    /// \param vector<QImage> image to update
    void updateImage(std::vector<QImage>);

    /// \brief changeFrame change current frame to frame with the passed ID.
    /// \param id the ID of the frame.
    void changeFrame(int id);

public slots:

    /// \brief sendImages emits images
    void sendImages();

    /// \brief frameButtonPressed change current frame to clicked frame
    void frameButtonPressed();

    /// \brief updateImageSizeTo16 clears images and sets new image sizes to 16x16
    void updateImageSizeTo16();

    /// \brief updateImageSizeTo32 clears images and sets new image sizes to 32x32
    void updateImageSizeTo32();

    /// \brief updateImageSizeTo64 clears images and sets new image sizes to 64x64
    void updateImageSizeTo64();
};

#endif // FRAME_H
