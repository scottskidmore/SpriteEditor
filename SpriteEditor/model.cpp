#include "model.h"
#include <QFileDialog>
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
        int size = a.frames[i]->imageSize;
        QImage image(size, size, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter paint(&image);
        for (int j = 0; j < (int)a.frames[i]->images.size(); j++) {
            paint.drawPixmap(0, 0, size, size, QPixmap::fromImage(a.frames[i]->images[j]));
        }
        imageList.push_back(image);
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

    f->sendImages();
    getFrameImages();
}

void model::handleDrawingShapes(QPoint startPoint, QPoint endPoint) {
    // Determine the size of the shape to be drawn
    int width = abs(endPoint.x() - startPoint.x());
    int height = abs(endPoint.y() - startPoint.y());
    int size = qMax(width, height);

    if (currentTool == Circle){
        pen.drawCircle(startPoint, size);
    }
    else if (currentTool == Square){
        pen.drawSquare(startPoint, size);
    }

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
    animationData["frameSize"] = a.frames[0]->imageSize;
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

                    QRgb pixelAlph = row[width];
                    int alpha = qAlpha(pixelAlph);

                    qDebug() << alpha;
                    QJsonObject pixel;
                    QColor color(row[width]);
                    pixel["red"] = color.red();
                    pixel["green"] = color.green();
                    pixel["blue"] = color.blue();
                    pixel["alpha"] = alpha;
                    //qDebug() << color.alpha();

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

    QJsonDocument docTest(animationData);
    QByteArray dataTest = docTest.toJson(QJsonDocument::Indented);
    //qDebug() << "serialized: " << dataTest;

    QFile fileTest(QString("testBasic2.json"));

    if (fileTest.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileTest);
        out << dataTest;
        fileTest.close();
        //qDebug() << "written";
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

void model::loadPressed(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading";
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Failed to parse JSON:" << jsonError.errorString();
        return;
    }



    // QJsonParseError err;
    // QJsonDocument doc = QJsonDocument::fromJson(jsonData, &err);

    // if(err.error != QJsonParseError::NoError)
    // {
    //     return; //-1; // Failure
    // }

    QJsonObject animation = jsonDoc.object();
    QJsonArray framesArray = animation.value("frames").toArray();
    a.frames[0]->imageSize = animation["frameSize"].toInt();
    // if (a.frames[0]->imageSize == 16){
    //     for (auto frame : a.frames){
    //         frame->updateImageSize16();
    //     }
    // }
    // else if (a.frames[0]->imageSize == 32){
    //     for (auto frame : a.frames){
    //         frame->updateImageSize32();
    //     }
    // }
    // else if (a.frames[0]->imageSize == 64){
    //     for (auto frame : a.frames){
    //         frame->updateImageSize64();
    //     }
    // }
    for(int i = 0; i < framesArray.size(); ++i)
    {
        QJsonObject obj = framesArray[i].toObject();
        QJsonArray layersArray = obj.value("layers").toArray();

        Frame* newF = new Frame();
        newF->frameID = (int)a.frames.size();
        // a.addFrame(newF);
        // switchFrame(newF->frameID);
        // emit connectFrameButton();

        for(int j = 0; j < layersArray.size(); ++j)
        {
            QJsonObject layerObj = layersArray[j].toObject();
            QJsonArray pixelsArray = layerObj.value("pixels").toArray();
            qDebug() << pixelsArray.size();
            for(int k = 0; k < pixelsArray.size(); ++k)
            {
                int width = 32;
                int x = k % width;
                int y = k / width;
                QPoint point(x, y);

                QJsonObject pixelObj = pixelsArray[k].toObject();
                int red = pixelObj["red"].toInt();
                int green = pixelObj["green"].toInt();
                int blue = pixelObj["blue"].toInt();
                int alpha = pixelObj["alpha"].toInt();

                QColor color(red, green, blue, alpha);
                newF->images[j].setPixelColor(point, color);

            }
            //a.frames[i] =
        }
        if (i == 0)
        {
            a.frames[0] = newF;
        }
        else
        {
            a.addFrame(newF);
            switchFrame(newF->frameID);
            emit connectFrameButton();
        }
    }
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
    this->f->setCurrentLayer(0);
}

void model::layer2(){
    this->f->setCurrentLayer(1);
}

void model::layer3(){
    this->f->setCurrentLayer(2);
}

void model::layer4(){
    this->f->setCurrentLayer(3);
}

void model::layer5(){
    this->f->setCurrentLayer(4);
}

void model::clearAll()
{
    a.frames.clear();
    this->f = new Frame();
    f->frameID = 0;
    a.addFrame(f);
    setDrawLayer();
    emit connectFrameUpdate();
    f->sendImages();
    getFrameImages();
}

void model::addFrame()
{
    Frame* newF = new Frame();
    newF->frameID = (int)a.frames.size();
    if (a.frames[0]->imageSize == 16){
        newF->updateImageSize16();
    }
    else if (a.frames[0]->imageSize == 32){
        newF->updateImageSize32();
    }
    else if (a.frames[0]->imageSize == 64){
        newF->updateImageSize64();
    }
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

void model::updateAllFrameSizes(){
    QObject *senderObject = QObject::sender();
    if (senderObject->objectName() == "size16"){
        for (auto frame : a.frames){
            frame->updateImageSize16();
        }
    }
    else if (senderObject->objectName() == "size32"){
        for (auto frame : a.frames){
            frame->updateImageSize32();
        }
    }
    else if (senderObject->objectName() == "size64"){
        for (auto frame : a.frames){
            frame->updateImageSize64();
        }
    }
    getFrameImages();
}

void model::updateFrameRate(int rate)
{
    a.setfps(rate);
}

