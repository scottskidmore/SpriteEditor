#include "frame.h"

Frame::Frame() {}

void Frame::drawPixel(QPoint)
{

}

void Frame::sendImages()
{
    emit updateImage(images);
}
