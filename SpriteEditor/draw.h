#ifndef DRAW_H
#define DRAW_H

#include <QPainter>

class Draw
{
public:
    Draw();
    int getLineWdith();
    void setLineWdith(int);
    QColor getColor();
    void setColor(QColor);
    void drawSquare(QPoint, int);
    void drawCircle(QPoint, int);
    void drawTraingle(QPoint, int);
    void drawSpray(QPoint, int);

private:
    QColor color;
    int lineWidth;
};

#endif // DRAW_H
