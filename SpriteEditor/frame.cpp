#include "frame.h"

Frame::Frame(QObject *parent)
{
    QImage newImage(32, 32, QImage::Format_ARGB32);
    //newImage.setPixelColor(16, 16, Qt::blue);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    currentImage = 0;
}

void Frame::drawPixel(QPoint point)
{
    images[0].setPixelColor(point, Qt::black);
}

QImage& Frame::getCurrentLayer()
{
    return images[currentImage];
}

void Frame::sendImages()
{
    emit updateImage(images);
}
