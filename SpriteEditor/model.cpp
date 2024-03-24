#include "model.h"

//model::model() {}
void model::drawImage(QPoint p)
{
    pen.drawPixel(p);
    f.sendImages();
}

