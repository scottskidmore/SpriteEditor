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

void Draw::drawSquare(QPoint p , int width)
{
    QPainter painter(this->image);
    painter.setPen(color);
    //painter.setBrush(color);
    painter.drawRect(p.x(), p.y(), width, width);
}

void Draw::drawCircle(QPoint p, int diameter)
{
    QPainter painter(this->image);
    painter.setPen(color);
    //painter.setBrush(color);
    painter.drawEllipse(p.x(), p.y(), diameter, diameter);
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
