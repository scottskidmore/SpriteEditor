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
    image->setPixelColor(point, Qt::black);
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
