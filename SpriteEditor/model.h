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
    //char currentTool;
    enum tools {Pen, Eraser, Square, Circle};
    tools currentTool;

public slots:
    void editImage(QPoint);
    void erasePressed();
    void drawPressed();
    void savePressed();
    void layer1();
    void layer2();
    void layer3();
    void layer4();
    void layer5();
};

#endif // MODEL_H
