#include "frame.h"
//Drew Humphrey
Frame::Frame(QObject *parent)
{
    QImage newImage(32, 32, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    currentImage = 0;
    imageSize = 32;
}

void Frame::drawPixel(QPoint point)
{
    images[currentImage].setPixelColor(point, Qt::black);
}

QImage& Frame::getCurrentLayer()
{
    return images[currentImage];
}

void Frame::sendImages()
{
    emit updateImage(images);
}

void Frame::frameButtonPressed()
{
    emit changeFrame(this->frameID);
}

void Frame::updateImageSizeTo16()
{
    images.clear();
    QImage newImage(16, 16, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    imageSize = 16;
    emit updateImage(images);
}

void Frame::updateImageSizeTo32()
{
    images.clear();
    QImage newImage(32, 32, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    imageSize = 32;
    emit updateImage(images);
}

void Frame::updateImageSizeTo64()
{
    images.clear();
    QImage newImage(64, 64, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    imageSize = 64;
    emit updateImage(images);
}

void Frame::setCurrentLayer(int i)
{
    currentImage=i;
}
