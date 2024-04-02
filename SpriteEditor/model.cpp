#include "model.h"

/// Reviewed by Adam Bently and Patrick Schlegel
Model::Model(QObject *parent)
    : QObject{parent}
{
    currentTool = Pen;
    f = new Frame();
    f->frameID = 0;
    a.addFrame(f);
}

void Model::setDrawLayer()
{
    pen.setImage(f->getCurrentLayer());
    emit swapLayerText(QString("Using Layer: %1").arg(f->currentImage + 1));
}

void Model::getFrameImages()
{
    std::vector<QImage> imageList;
    for (int i = 0; i < (int)a.frames.size(); i++) // Loop through frames
    {
        int size = a.frames[i]->imageSize;
        QImage image(size, size, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter paint(&image);
        for (int j = 0; j < (int)a.frames[i]->images.size(); j++)
        {
            paint.drawPixmap(0, 0, size, size, QPixmap::fromImage(a.frames[i]->images[j]));
        }
        imageList.push_back(image);
    }
    emit updateFrameDisplay(imageList);
}

void Model::editImage(QPoint p)
{
    setDrawLayer();
    if (currentTool == Pen)
    {
        pen.drawPixel(p);
    }
    else if (currentTool == Eraser)
    {
        pen.eraseTool(p);
    }
    else if (currentTool == SprayCan)
    {
        pen.sprayPaint(p, 6, 1);
    }
    f->sendImages();
    getFrameImages();
}

void Model::handleDrawingShapes(QPoint startPoint, QPoint endPoint)
{
    // Determine the size of the shape to be drawn
    int width = abs(endPoint.x() - startPoint.x());
    int height = abs(endPoint.y() - startPoint.y());
    int size = qMax(width, height);
    if (currentTool == Circle)
    {
        pen.drawCircle(startPoint, size);
    }
    else if (currentTool == Square)
    {
        pen.drawSquare(startPoint, size);
    }
    f->sendImages();
    getFrameImages();
}

void Model::erasePressed()
{
    currentTool = Eraser;
}

void Model::drawPressed()
{
    currentTool = Pen;
}

void Model::savePressed(QString path)
{
    QJsonObject animationData;
    QJsonArray frames;
    int count = 0;

    animationData["frameSize"] = a.frames[0]->imageSize;
    for (auto frame : a.frames) // loop through the frames
    {
        QJsonObject frameObj;
        QJsonArray layers;
        frameObj["frameID"] = frame->frameID;
        frameObj["layers"] = layers;
        for (auto layer : frame->images) // loop through the layers in each frame
        {
            QJsonObject image;
            image["layerID"] = count;
            QJsonArray pixels;

            for (int height = 0; height < layer.height(); height++) // now go thorugh the pixels
            {
                QRgb *row = (QRgb*) layer.scanLine(height);
                for (int width = 0; width < layer.width(); width++)
                {
                    // get the pixel colors and write them to the JSON
                    QRgb pixelAlph = row[width];
                    int alpha = qAlpha(pixelAlph);
                    QJsonObject pixel;
                    QColor color(row[width]);

                    pixel["red"] = color.red();
                    pixel["green"] = color.green();
                    pixel["blue"] = color.blue();
                    pixel["alpha"] = alpha;
                    pixels.append(pixel);
                }
            }
            // add the pixels to the layer
            image.insert("pixels", pixels);
            layers.append(image);
            count++;
        }
        // add the layers to the frames
        frameObj.insert("layers", layers);
        frames.append(frameObj);
    }
    // add the frames to the animation
    animationData.insert("frames", frames);

    QJsonDocument doc(animationData);
    QByteArray data = doc.toJson(QJsonDocument::Indented);
    int lastPoint = path.lastIndexOf(".");
    QString pathNoJson = path.left(lastPoint);
    QFile file(pathNoJson += ".ssp");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) // write the JSON data to the file
    {
        QTextStream out(&file);
        out << data;
        file.close();
    }
    else { // if we cant save the file
        qDebug() << "Error saving file";
    }
}

void Model::loadPressed(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // if we cant read the file
    {
        qDebug() << "Failed to open file for reading";
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) // if we cant read the JSON
    {
        qDebug() << "Failed to parse JSON:" << jsonError.errorString();
        return;
    }

    // initial setup, clear the animation, and set the proper image size
    emit clearAnimation();
    QJsonObject animation = jsonDoc.object();
    QJsonArray framesArray = animation.value("frames").toArray();
    int frameSize = animation["frameSize"].toInt();
    this->a.frames[0]->imageSize = frameSize;
    emit updateLoadImageSize(frameSize);

    for(int i = 0; i < framesArray.size(); ++i) // loop through the frames
    {
        QJsonObject obj = framesArray[i].toObject();
        QJsonArray layersArray = obj.value("layers").toArray();

        Frame* newF = new Frame();
        newF->frameID = (int)a.frames.size();
        updateFrameSizeInt(frameSize, newF);

        for(int j = 0; j < layersArray.size(); ++j) // loop through the layers
        {
            QJsonObject layerObj = layersArray[j].toObject();
            QJsonArray pixelsArray = layerObj.value("pixels").toArray();
            qDebug() << pixelsArray.size();
            for(int k = 0; k < pixelsArray.size(); ++k) // loop through the pixels
            {
                // get the x and y from the array index
                int width = frameSize;
                int x = k % width;
                int y = k / width;
                QPoint point(x, y);

                QJsonObject pixelObj = pixelsArray[k].toObject();
                int red = pixelObj["red"].toInt();
                int green = pixelObj["green"].toInt();
                int blue = pixelObj["blue"].toInt();
                int alpha = pixelObj["alpha"].toInt();

                // set the pixel at the x and y values to the color
                QColor color(red, green, blue, alpha);
                newF->images[j].setPixelColor(point, color);
            }
        }
        if (i == 0) // if its the first frame
        {
            a.frames[0] = newF;
        }
        else // otherwise make a new frame
        {
            a.addFrame(newF);
            switchFrame(newF->frameID);
            emit connectFrameButton();
        }
    }
    // update the frame display and set the saved fps
    getFrameImages();
    emit loadFps(1);
}

int Model::getFrameCount()
{
    return (int)a.frames.size();
}

void Model::circlePressed()
{
    currentTool = Circle;
}

void Model::squarePressed()
{
    currentTool = Square;
}

void Model::sprayCanPressed()
{
    currentTool = SprayCan;
}

void Model::layer1()
{
    this->f->setCurrentLayer(0);
    emit swapLayerText(QString("Using Layer: %1").arg(f->currentImage + 1));
}

void Model::layer2()
{
    this->f->setCurrentLayer(1);
    emit swapLayerText(QString("Using Layer: %1").arg(f->currentImage + 1));
}

void Model::layer3()
{
    this->f->setCurrentLayer(2);
    emit swapLayerText(QString("Using Layer: %1").arg(f->currentImage + 1));
}

void Model::layer4()
{
    this->f->setCurrentLayer(3);
    emit swapLayerText(QString("Using Layer: %1").arg(f->currentImage + 1));
}

void Model::layer5()
{
    this->f->setCurrentLayer(4);
    emit swapLayerText(QString("Using Layer: %1").arg(f->currentImage + 1));
}

void Model::clearAll()
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

void Model::addFrame()
{
    Frame* newF = new Frame();
    newF->frameID = (int)a.frames.size();
    // update the image size for the respective dimenstions
    if (a.frames[0]->imageSize == 16)
    {
        newF->updateImageSizeTo16();
    }
    else if (a.frames[0]->imageSize == 32)
    {
        newF->updateImageSizeTo32();
    }
    else if (a.frames[0]->imageSize == 64)
    {
        newF->updateImageSizeTo64();
    }
    a.addFrame(newF);
    switchFrame(newF->frameID);
    emit connectFrameButton();
}

void Model::switchFrame(int id)
{
    this->f = a.frames[id];
    setDrawLayer();
    emit connectFrameUpdate();
    f->sendImages();
    getFrameImages();
}

void Model::deleteFrame()
{
    if (a.frames.size() > 1)
    {
        a.frames.pop_back();
    }
    switchFrame(a.frames[a.frames.size() - 1]->frameID);
    getFrameImages();
}

void Model::updateAllFrameSizes()
{
    QObject *senderObject = QObject::sender();
    int size = 10;
    if (senderObject->objectName() == "size16" || size == 16)
    {
        for (auto frame : a.frames){
            frame->updateImageSizeTo16();
        }
    }

    else if (senderObject->objectName() == "size32" || size == 32)
    {
        for (auto frame : a.frames){
            frame->updateImageSizeTo32();
        }
    }

    else if (senderObject->objectName() == "size64" || size == 64)
    {
        for (auto frame : a.frames){
            frame->updateImageSizeTo64();
        }
    }
    getFrameImages();
}

void Model::updateFrameSizeInt(int size, Frame* frame)
{
    if (size == 16)
        frame->updateImageSizeTo16();

    else if (size == 32)
        frame->updateImageSizeTo32();

    else if (size == 64)
        frame->updateImageSizeTo64();
}

void Model::updateFrameRate(int rate)
{
    a.setfps(rate);
}
