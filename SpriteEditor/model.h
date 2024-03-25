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
    char currentTool;

public slots:
    void editImage(QPoint);
    void erasePressed();
    void drawPressed();
    void savePressed();
};

#endif // MODEL_H
