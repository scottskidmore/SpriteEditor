#include "frame.h"

Frame::Frame(QObject *parent)
{
    QImage newImage(32, 32, QImage::Format_ARGB32);
    //newImage.setPixelColor(16, 16, Qt::blue);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    currentImage = 0;
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

void Frame::updateImageSize16(){
    images.clear();
    QImage newImage(16, 16, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    emit updateImage(images);
}

void Frame::updateImageSize32(){
    images.clear();
    QImage newImage(32, 32, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    emit updateImage(images);
}

void Frame::updateImageSize64(){
    images.clear();
    QImage newImage(64, 64, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    images.push_back(newImage);
    emit updateImage(images);
}
 void Frame::setCurrentLayer(int i){
    currentImage=i;
}
