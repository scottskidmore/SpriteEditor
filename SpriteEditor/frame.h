#ifndef FRAME_H
#define FRAME_H

#include <list>
#include <QImage>

class Frame
{
public:
    Frame();
    void drawPixel(QPoint);

private:
    std::list<QImage> images;
    int frameID;
    int currentImage;

signals:
    void updateImage(QImage);
};

#endif // FRAME_H
