#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>

class Canvas : public QLabel
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void setGridSize(int size);
    void drawGrid();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int gridSize;
    bool trackMouse;
    int cellSize;


signals:
    void gridClicked(QPoint);
};

#endif // CANVAS_H
