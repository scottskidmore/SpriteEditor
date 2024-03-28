#ifndef MODEL_H
#define MODEL_H

#include "draw.h"
#include "animation.h"
#include "qobject.h"
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QPushButton>
#include <QObject>

class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = nullptr);
    //model();
    Draw pen;
    Animation a;
    Frame* f;
    void setDrawLayer();


private:
    //char currentTool;
    enum tools {Pen, Eraser, Square, Circle};
    tools currentTool;
    void getFrameImages();

signals:
    void connectFrameButton();
    void connectFrameUpdate();
    void updateFrameDisplay(std::vector<QImage> images);

public slots:
    void editImage(QPoint);
    void erasePressed();
    void drawPressed();
    void savePressed();
    void addFrame();
    void switchFrame(int id);
    void deleteFrame();
};

#endif // MODEL_H
