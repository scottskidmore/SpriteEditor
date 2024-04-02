#include "canvas.h"

/// Reviewed by Scott Skidmore
Canvas::Canvas(QWidget *parent) : QLabel{parent}
{
    setMouseTracking(true);
    trackMouse = false;
}

void Canvas::setGridSize(int size)
{
    this->gridSize = size;
    cellSize = 512 / gridSize;
}


void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::lightGray);
    pen.setWidth(1);
    painter.setPen(pen);

    for (int i = 0; i < gridSize+1; i++) {
        int xy = i * (512/gridSize);
        painter.drawLine(xy, 0, xy, 512);
        painter.drawLine(0, xy, 512, xy);
    }

    if (!layers.empty()) {
        for(QImage layer : layers){
            painter.drawPixmap(0, 0,512,512, QPixmap::fromImage(layer));
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (trackMouse) {
        if (event->pos().x() <= 512 && event->pos().y() <= 512 && event->pos().x() >= 0 && event->pos().y() >= 0) {
            int x = event->pos().x() / cellSize;
            int y = event->pos().y() / cellSize;
            emit gridClicked(QPoint(x, y));
        }
        QWidget::update();
    }

    //QWidget::update();

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x() / cellSize;
    int y = event->pos().y() / cellSize;
    emit gridClicked(QPoint(x, y));
    QWidget::update();
    startPoint = (QPoint(x, y));
    trackMouse = true;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (trackMouse) {
        int x = event->pos().x() / cellSize;
        int y = event->pos().y() / cellSize;
        endPoint = (QPoint(x, y));
        emit drawingAction(startPoint, endPoint);
        trackMouse = false;  // Stop tracking the mouse
    }

    update();
}

void Canvas::updateCanvas(std::vector<QImage> newLayers)
{
    std::swap(layers, newLayers);
}

void Canvas::updateGridSizeTo16(){

    setGridSize(16);
    QWidget::update();
}

void Canvas::updateGridSizeTo32()
{

    setGridSize(32);
    QWidget::update();
}

void Canvas::updateGridSizeTo64()
{

    setGridSize(64);
    QWidget::update();
}

void Canvas::loadPressed()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    QWidget::update();
}
