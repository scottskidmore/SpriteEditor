#include "model.h"

//model::model() {}

model::model(QObject *parent)
    : QObject{parent}
{
    //currentTool = 'd';

    currentTool = Pen;
    f = new Frame();
    f->frameID = 0;
    a.addFrame(f);
    //QObject::connect(f, &Frame::changeFrame, this, &model::switchFrame);
}

void model::setDrawLayer()
{
    pen.setImage(f->getCurrentLayer());
}

void model::getFrameImages()
{
    std::vector<QImage> imageList;
    for(int i = 0; i < (int)a.frames.size(); i++) {
        imageList.push_back(a.frames[i]->images[0]);
    }

    emit updateFrameDisplay(imageList);
}

void model::editImage(QPoint p)
{
    if (currentTool == Pen)
        pen.drawPixel(p);
    else if (currentTool == Eraser)
        pen.eraseTool(p);

    f->sendImages();
    getFrameImages();
}

void model::erasePressed()
{
    currentTool = Eraser;
}

void model::drawPressed()
{
    currentTool = Pen;
}

void model::savePressed()
{
    QJsonObject json;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    f->getCurrentLayer().save(&buffer, "PNG");

    QString base64Image = QString::fromLatin1(byteArray.toBase64().data());

    json["image"] = base64Image;

    qDebug() << json;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(QJsonDocument::Indented);
    qDebug() << "serialized: " << data;

    QFile file(QString("testJson.json"));

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << data;
        file.close();
        qDebug() << "written";
    }

    QFile file2(QString("testJson.json"));
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray imagejsonData = file2.readAll();
    file2.close();
    QJsonDocument doc2 = QJsonDocument::fromJson(imagejsonData);
    QJsonObject jsonImage = doc2.object();
    QString baseImage = jsonImage["image"].toString();
    QByteArray imageData = QByteArray::fromBase64(baseImage.toLatin1());
    QImage testImage;
    testImage.loadFromData(imageData);

    testImage.save("testImage.png", "PNG");
}

void model::addFrame()
{
    Frame* newF = new Frame();
    newF->frameID = (int)a.frames.size();
    a.addFrame(newF);
    switchFrame(newF->frameID);
    emit connectFrameButton();
}

void model::switchFrame(int id)
{
    this->f = a.frames[id];
    setDrawLayer();
    emit connectFrameUpdate();
    f->sendImages();
    getFrameImages();
}

