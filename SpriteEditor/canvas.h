#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPoint>
#include <QPainter>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

private:
    int gridSize;


signals:
    void gridClicked(QPoint);
};

#endif // CANVAS_H
