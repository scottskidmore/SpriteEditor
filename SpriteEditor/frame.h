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
    int frameID;
    void setCurrentLayer(int);
    std::vector<QImage> images;

private:
    int currentImage;

signals:
    void updateImage(std::vector<QImage>);

public slots:
    void sendImages();
    void updateImageSize16();
    void updateImageSize32();
    void updateImageSize64();
};

#endif // FRAME_H
