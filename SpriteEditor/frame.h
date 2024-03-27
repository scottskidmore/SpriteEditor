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
    std::vector<QImage> images;


private:
    //std::vector<QImage> images;

    int currentImage;

signals:
    void updateImage(std::vector<QImage>);
    void changeFrame(int id);

public slots:
    void sendImages();
    void frameButtonPressed();
};

#endif // FRAME_H
