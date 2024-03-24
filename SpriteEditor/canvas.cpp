#include "canvas.h"
#include <QDebug>

Canvas::Canvas(QWidget *parent)
    : QLabel{parent}
{
    setMouseTracking(true);
    trackMouse = false;
}

void Canvas::setGridSize(int size)
{
    this->gridSize = size;
    cellSize = 512/gridSize;
}

void Canvas::drawGrid()
{
    for (int i = 0; i < gridSize; i++) {

    }
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen(Qt::lightGray);
    pen.setWidth(1);
    painter.setPen(pen);

    for (int i = 0; i < gridSize+1; i++) {
        int xy = i * (512/gridSize);
        painter.drawLine(xy, 0, xy, 512); //vertical line
        painter.drawLine(0, xy, 512, xy);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (trackMouse) {
        if (event->pos().x() <= 512 && event->pos().y() <= 512 && event->pos().x() >= 0 && event->pos().y() >= 0) {
            int x = event->pos().x() / cellSize;
            int y = event->pos().y() / cellSize;
            emit gridClicked(QPoint(x, y));
            qDebug() << "Tracking Mouse move: " << x << " " << y;
        }

    }

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse pressed: " << event->pos();
    trackMouse = true;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Mouse released: " << event->pos();
    trackMouse = false;
}

