#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <vector>

class Canvas : public QLabel
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void setGridSize(int size);
    void drawGrid();

    std::vector<QImage> layers;

//protected:
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
public slots:
    void updateCanvas(std::vector<QImage>);
    void updateGridSize16();
    void updateGridSize32();
    void updateGridSize64();
};

#endif // CANVAS_H
