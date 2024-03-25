#include "draw.h"

Draw::Draw(QObject *parent)
    : QObject{parent}
{

}

int Draw::getLineWdith()
{

}

void Draw::setLineWdith(int)
{

}

QColor Draw::getColor()
{

}

void Draw::setColor(QColor)
{

}

void Draw::drawSquare(QPoint, int)
{

}

void Draw::drawCircle(QPoint, int)
{

}

void Draw::drawTraingle(QPoint, int)
{

}

void Draw::drawSpray(QPoint, int)
{

}

void Draw::drawPixel(QPoint point)
{
    //QRgb black = qRgb(0, 0, 0);
    image->setPixelColor(point, Qt::black);
}

void Draw::setImage(QImage& image)
{
    this->image = &image;
}

void Draw::drawImage(QPoint point)
{

}
