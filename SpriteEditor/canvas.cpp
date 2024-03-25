#include "canvas.h"
#include <QDebug>
#include <QImageWriter>

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
    qDebug() << "not printing layer, layersSize: " << layers.size();
    // change later for layers
    if (!layers.empty()) {
        qDebug() << "printing layer, layersSize: " << layers.size();
        QPixmap map = QPixmap::fromImage(layers[0]);
        map = map.scaled(512, 512);
        map.toImage().save(QString("image2.png"));
        painter.drawPixmap(0, 0, 512, 512, map);
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

    QWidget::update();

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse pressed: " << event->pos();
    int x = event->pos().x() / cellSize;
    int y = event->pos().y() / cellSize;
    emit gridClicked(QPoint(x, y));
    QWidget::update();
    trackMouse = true;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Mouse released: " << event->pos();
    trackMouse = false;

}

void Canvas::updateCanvas(std::vector<QImage> newLayers)
{
    std::swap(layers, newLayers);
}

