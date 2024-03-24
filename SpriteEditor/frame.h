#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include "qobject.h"
#include <vector>

class Frame : public QObject
{
    Q_OBJECT
public:
    explicit Frame(QObject *parent = nullptr);
    void drawPixel(QPoint);
    QImage& getCurrentLayer();

private:
    std::vector<QImage> images;
    int frameID;
    int currentImage;

signals:
    void updateImage(std::vector<QImage>);

public slots:
    void sendImages();
};

#endif // FRAME_H
