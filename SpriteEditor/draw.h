#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include "qobject.h"

class Draw : public QObject
{
    Q_OBJECT
public:
    explicit Draw(QObject *parent = nullptr);
    int getLineWdith();
    void setLineWdith(int);
    QColor getColor();
    void setColor(QColor);
    void drawSquare(QPoint, int);
    void drawCircle(QPoint, int);
    void drawTraingle(QPoint, int);
    void drawSpray(QPoint, int);
    //void drawPixel(QPoint);
    void setImage(QImage&);

private:
    QColor color;
    int lineWidth;
    QImage image;

public slots:
    void drawImage(QPoint);
    void drawPixel(QPoint);
signals:
    void imageUpdated();
};

#endif // DRAW_H
