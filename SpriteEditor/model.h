#ifndef MODEL_H
#define MODEL_H

#include "draw.h"
#include "animation.h"
#include "qobject.h"

class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = nullptr);
    //model();
    Draw pen;
    Animation a;
    Frame f;
    void setDrawLayer();


private:

public slots:
    void drawImage(QPoint);
};

#endif // MODEL_H
