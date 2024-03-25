#include "draw.h"

Draw::Draw(QObject *parent)
    : QObject{parent}
{
    color = Qt::black;
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

void Draw::setColor(QColor c)
{
    color = c;
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
    image->setPixelColor(point, color);
}

void Draw::setImage(QImage& image)
{
    this->image = &image;
}

void Draw::eraseTool(QPoint point)
{
    image->setPixelColor(point, Qt::transparent);
}

QImage Draw::getImage()
{
    return *image;
}

void Draw::drawImage(QPoint point)
{

}
