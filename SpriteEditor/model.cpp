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
    setDrawLayer();
    if (currentTool == Pen)
        pen.drawPixel(p);
    else if (currentTool == Eraser)
        pen.eraseTool(p);
    else if (currentTool == Circle)
        pen.drawCircle(p, 5);
    else if (currentTool == Square)
        pen.drawSquare(p, 5);

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
    QJsonObject animationData;
    QJsonArray frames;
    int count = 0;

    animationData["fps"] = a.fps;
    for (auto frame : a.frames)
    {
        QJsonObject frameObj;
        QJsonArray layers;
        frameObj["frameID"] = frame->frameID;
        frameObj["layers"] = layers;
        //frames.append(frameObj);
        //for (auto pixel : )

        for (auto layer : frame->images)
        {
            QJsonObject image;
            image["layerID"] = count;
            QJsonArray pixels;
            //image["pixels"] = pixels;
            //pixels = layer->pixels;
            //frames.pixels;
            for (int height = 0; height < layer.height(); height++){
                QRgb *row = (QRgb*) layer.scanLine(height);
                for (int width = 0; width < layer.width(); width++){
                    QJsonObject pixel;
                    QColor color(row[width]);
                    pixel["red"] = color.red();
                    pixel["green"] = color.green();
                    pixel["blue"] = color.blue();
                    pixel["alpha"] = color.alpha();

                    //pixel.insert("RGB value: " , row[width].toObject());
                    //pixel["rgbValue"] = pixel;
                    pixels.append(pixel);
                }
            }
            image.insert("pixels", pixels);
            layers.append(image);
            count++;
        }
        frameObj.insert("layers", layers);

        frames.append(frameObj);
    }
    animationData.insert("frames", frames);

    QFile fileTest(QString("testBasic2.json"));

    if (fileTest.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileTest);
        out << dataTest;
        fileTest.close();
        qDebug() << "written";
    }













    //old code
    // QJsonObject json;

    // QByteArray byteArray;
    // QBuffer buffer(&byteArray);
    // buffer.open(QIODevice::WriteOnly);
    // f.getCurrentLayer().save(&buffer, "PNG");

    // QString base64Image = QString::fromLatin1(byteArray.toBase64().data());

    // json["image"] = base64Image;

    // qDebug() << json;

    // QJsonDocument doc(json);
    // QByteArray data = doc.toJson(QJsonDocument::Indented);
    // qDebug() << "serialized: " << data;

    // QFile file(QString("testJson.json"));

    // if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    //     QTextStream out(&file);
    //     out << data;
    //     file.close();
    //     qDebug() << "written";
    // }

    // QFile file2(QString("testJson.json"));
    // file2.open(QIODevice::ReadOnly | QIODevice::Text);
    // QByteArray imagejsonData = file2.readAll();
    // file2.close();
    // QJsonDocument doc2 = QJsonDocument::fromJson(imagejsonData);
    // QJsonObject jsonImage = doc2.object();
    // QString baseImage = jsonImage["image"].toString();
    // QByteArray imageData = QByteArray::fromBase64(baseImage.toLatin1());
    // QImage testImage;
    // testImage.loadFromData(imageData);

    // testImage.save("testImage.png", "PNG");
}

void model::circlePressed()
{
    currentTool = Circle;
}

void model::squarePressed()
{
    currentTool = Square;
}

void model::layer1(){
    this->f.setCurrentLayer(0);
}

void model::layer2(){
    this->f.setCurrentLayer(1);
}

void model::layer3(){
    this->f.setCurrentLayer(2);
}

void model::layer4(){
    this->f.setCurrentLayer(3);
}

void model::layer5(){
    this->f.setCurrentLayer(4);
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

void model::deleteFrame()
{
    if (a.frames.size() > 1)
    {
        a.frames.pop_back();
    }
    switchFrame(a.frames[a.frames.size() - 1]->frameID);
    getFrameImages();
    qDebug() << a.frames.size();
}

