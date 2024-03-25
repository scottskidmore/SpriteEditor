#include "model.h"

//model::model() {}

model::model(QObject *parent)
    : QObject{parent}
{}

void model::setDrawLayer()
{
    pen.setImage(f.getCurrentLayer());
}

void model::drawImage(QPoint p)
{
    pen.drawPixel(p);
    //f.drawPixel(p);
    f.sendImages();
}

