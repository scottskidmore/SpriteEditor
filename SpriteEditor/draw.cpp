#include "draw.h"
///Reviewed for code style by Paolo Diotaiuti

Draw::Draw(QObject *parent)
    : QObject{parent}
{
    color = Qt::black;
}

void Draw::setColor(QColor newColor)
{
    color = newColor;
}

void Draw::drawSquare(QPoint point , int width)
{
    QPainter painter(this->image);
    painter.setPen(color);
    painter.drawRect(point.x(), point.y(), width, width);
}

void Draw::drawCircle(QPoint point, int diameter)
{
    QPainter painter(this->image);
    painter.setPen(color);
    painter.drawEllipse(point.x(), point.y(), diameter, diameter);
}

void Draw::sprayPaint(QPoint center, int radius, int density)
{
    QPainter painter(this->image);
    painter.setPen(color);
    int pointsToDraw = radius * density;
    //finds random pixels within the radius to be drawn
    for (int i = 0; i < pointsToDraw; ++i)
    {
        int dx = QRandomGenerator::global()->bounded(-radius, radius);
        int dy = QRandomGenerator::global()->bounded(-radius, radius);
        if (dx * dx + dy * dy <= radius * radius)
        {
            painter.drawPoint(center.x() + dx, center.y() + dy);
        }
    }
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
