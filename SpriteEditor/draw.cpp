#include "draw.h"

Draw::Draw(QObject *parent)
    : QObject{parent}
{
    color = Qt::black;
}

// int Draw::getLineWdith()
// {

// }

// void Draw::setLineWdith(int)
// {

// }

// QColor Draw::getColor()
// {

// }

void Draw::setColor(QColor c)
{
    color = c;
}

void Draw::drawSquare(QPoint p , int width)
{
    QPainter painter(this->image);
    painter.setPen(color);
    painter.drawRect(p.x(), p.y(), width, width);
}

void Draw::drawCircle(QPoint p, int diameter)
{
    QPainter painter(this->image);
    painter.setPen(color);
    painter.drawEllipse(p.x(), p.y(), diameter, diameter);
}

void Draw::sprayPaint(QPoint center, int radius, int density)
{
    QPainter painter(this->image);
    painter.setPen(color);

    int pointsToDraw = radius * density;

    for (int i = 0; i < pointsToDraw; ++i) {
        int dx = QRandomGenerator::global()->bounded(-radius, radius);
        int dy = QRandomGenerator::global()->bounded(-radius, radius);

        if (dx * dx + dy * dy <= radius * radius) {
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

// void Draw::drawImage(QPoint point)
// {

// }
