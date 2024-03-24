#include "frame.h"

Frame::Frame(QObject *parent)
{
    QImage newImage(32, 32, QImage::Format_ARGB32);
    images.push_back(newImage);
    currentImage = 0;
}

void Frame::drawPixel(QPoint)
{

}

QImage& Frame::getCurrentLayer()
{
    return images[currentImage];
}

void Frame::sendImages()
{
    emit updateImage(images);
}
