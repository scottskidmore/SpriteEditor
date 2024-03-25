#include "model.h"

//model::model() {}

model::model(QObject *parent)
    : QObject{parent}
{
    currentTool = 'd';
}

void model::setDrawLayer()
{
    pen.setImage(f.getCurrentLayer());
}

void model::editImage(QPoint p)
{
    if (currentTool == 'd')
        pen.drawPixel(p);
    else if (currentTool == 'e')
        pen.eraseTool(p);

    f.sendImages();
}

void model::erasePressed()
{
    currentTool = 'e';
}

void model::drawPressed()
{
    currentTool = 'd';
}

void model::savePressed()
{
    QJsonObject json;

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    f.getCurrentLayer().save(&buffer, "PNG");

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

