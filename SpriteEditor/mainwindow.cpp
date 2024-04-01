#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include <QFileDialog>

MainWindow::MainWindow(Model *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setGridSize(32);
    timer.start(5);
    QObject::connect(ui->canvas,
            &Canvas::gridClicked,
            m,
            &Model::editImage);

    QObject::connect(m->f,
            &Frame::updateImage,
            ui->canvas,
            &Canvas::updateCanvas);

    QObject::connect(ui->ActionDraw,
            &QAction::triggered,
            m,
            &Model::drawPressed);

    QObject::connect(ui->actionSquare,
                     &QAction::triggered,
                     m,
                     &Model::squarePressed);

    QObject::connect(ui->actionCircle,
                     &QAction::triggered,
                     m,
                     &Model::circlePressed);
    QObject::connect(ui->actionSpray_Paint,
                     &QAction::triggered,
                     m,
                     &Model::sprayCanPressed);

    QObject::connect(ui->canvas,
                     &Canvas::drawingAction,
                     m,
                     &Model::handleDrawingShapes);

    QObject::connect(ui->actionErase,
            &QAction::triggered,
            m,
            &Model::erasePressed);

    QObject::connect(ui->actionSave,
                     &QAction::triggered,
                     this,
                     &MainWindow::saveDialog);

    // QObject::connect(ui->actionLoad,
    //                  &QAction::triggered,
    //                  m,
    //                  &model::loadPressed);

    QObject::connect(ui->actionLoad,
                     &QAction::triggered,
                     this,
                     &MainWindow::loadPressed);

    QObject::connect(ui->chooseColor,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::chooseColor);

    QObject::connect(m,
                     &Model::updateFrameDisplay,
                     this,
                     &MainWindow::updateFrameDisplay);

    QObject::connect(m,
                     &Model::updateFrameDisplay,
                     this,
                     &MainWindow::storeFrames);

    QObject::connect(ui->layer1,
                     &QPushButton::clicked,
                     m,
                     &Model::layer1);

    QObject::connect(ui->layer2,
                     &QPushButton::clicked,
                     m,
                     &Model::layer2);

    QObject::connect(ui->layer3,
                     &QPushButton::clicked,
                     m,
                     &Model::layer3);

    QObject::connect(ui->layer4,
                     &QPushButton::clicked,
                     m,
                     &Model::layer4);

    QObject::connect(ui->layer5,
                     &QPushButton::clicked,
                     m,
                     &Model::layer5);



    QObject::connect(ui->addFrameButton,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::onAddFrame);
    QObject::connect(ui->size16,
                     &QPushButton::clicked,
                     ui->canvas,
                     &Canvas::updateGridSize16);

    QObject::connect(ui->size32,
                     &QPushButton::clicked,
                     ui->canvas,
                     &Canvas::updateGridSize32);

    QObject::connect(ui->size64,
                     &QPushButton::clicked,
                     ui->canvas,
                     &Canvas::updateGridSize64);

    QObject::connect(ui->size16,
                     &QPushButton::clicked,
                     m,
                     &Model::updateAllFrameSizes);

    QObject::connect(ui->size32,
                     &QPushButton::clicked,
                     m,
                     &Model::updateAllFrameSizes);

    QObject::connect(ui->size64,
                     &QPushButton::clicked,
                     m,
                     &Model::updateAllFrameSizes);


    QObject::connect(ui->frame0,
                     &QPushButton::clicked,
                     m->f,
                     &Frame::frameButtonPressed);

    QObject::connect(m->f,
                     &Frame::changeFrame,
                     m,
                     &Model::switchFrame);

    QObject::connect(this,
                     &MainWindow::frameButtonAdded,
                     m,
                     &Model::addFrame);

    QObject::connect(m,
                     &Model::connectFrameButton,
                     this,
                     &MainWindow::connectButtonFrame);

    QObject::connect(m,
                     &Model::connectFrameUpdate,
                     this,
                     &MainWindow::connectNewFrame);

    QObject::connect(ui->removeFrameButton,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::onRemoveFrame);
    QObject::connect(this,
                     &MainWindow::frameButtonRemoved,
                     m,
                     &Model::deleteFrame);

    QObject::connect(ui->frameRateSlider,
                     &QSlider::sliderMoved,
                     this,
                     &MainWindow::updateFps);
    QObject::connect(m,
                     &Model::loadFps,
                     this,
                     &MainWindow::updateFps);

    QObject::connect(&timer,
                     &QTimer::timeout,
                     this,
                     &MainWindow::animate);
    QObject::connect(ui->actionNew,
                     &QAction::triggered,
                     this,
                     &MainWindow::onNewButtonPressed);
    QObject::connect(m,
                     &Model::clearAnimation,
                     this,
                     &MainWindow::onNewButtonPressed);

    QObject::connect(this,
                     &MainWindow::createNewSprite,
                     m,
                     &Model::clearAll);

    QObject::connect(ui->frameRateSlider,
                     &QSlider::sliderMoved,
                     m,
                     &Model::updateFrameRate);

    QObject::connect(ui->actionHelp,
                     &QAction::triggered,
                     this,
                     &MainWindow::helpClicked);

    QObject::connect(m,
                     &Model::swapLayerText,
                     this,
                     &MainWindow::changeUsingLayerText);

    QObject::connect(m,
                     &Model::updateLoadImageSize,
                     this,
                     &MainWindow::changeToLoadSize);


    m->setDrawLayer();
    this->m = m;
}


void MainWindow::chooseColor() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        ui->colorLabel->setStyleSheet("background-color: " + color.name() + ";");
        m->pen.setColor(color);
    }
}

void MainWindow::onAddFrame()
{
    QPushButton *button = new QPushButton(this);
    button->setMaximumSize(64, 64);
    button->setMinimumSize(64, 64);
    button->setGeometry(75, 10, 64, 64);
    ui->scrollFrameBox->addWidget(button);
    emit frameButtonAdded();
}

void MainWindow::updateFrameDisplay(std::vector<QImage> images)
{
    QObjectList children = ui->scrollAreaContents->children();
    for (int i = 1; i <= (int)images.size() && i < children.size(); i++) {
        QPushButton *c = qobject_cast<QPushButton*>(children[i]);
        QPixmap m;
        m.convertFromImage(images[i-1]);
        QIcon icon(m.scaled(60, 60));
        c->setIcon(icon);
        c->setIconSize(QSize(64, 64));
    }
}

void MainWindow::connectButtonFrame()
{
    QObjectList children = ui->scrollAreaContents->children();
    int index = children.size() - 1;
    if (index < m->getFrameCount()) {
        QPushButton *button = new QPushButton(this);
        button->setMaximumSize(64, 64);
        button->setMinimumSize(64, 64);
        button->setGeometry(75, 10, 64, 64);
        ui->scrollFrameBox->addWidget(button);
    }
    QObject::connect(qobject_cast<QPushButton*>(ui->scrollAreaContents->children().last()), &QPushButton::clicked, m->a.frames.back(), &Frame::frameButtonPressed);
    QObject::connect(m->a.frames.back(), &Frame::changeFrame, m, &Model::switchFrame);
}

void MainWindow::connectNewFrame()
{
    QObject::connect(m->f,
                     &Frame::updateImage,
                     ui->canvas,
                     &Canvas::updateCanvas);
    ui->canvas->update();
}

void MainWindow::onRemoveFrame()
{
    QObjectList children = ui->scrollAreaContents->children();
    int index = children.size() - 1;
    if (index > 1) {
        QPushButton *c = qobject_cast<QPushButton*>(children[index]);
        ui->scrollFrameBox->removeWidget(c);
        delete c;
        QObject::disconnect(qobject_cast<QPushButton*>(ui->scrollAreaContents->children().last()), &QPushButton::clicked, m->a.frames.back(), &Frame::frameButtonPressed);
        QObject::disconnect(m->a.frames.back(), &Frame::changeFrame, m, &Model::switchFrame);
        ui->scrollFrameBox->update();
        emit frameButtonRemoved();
    }
    ui->canvas->update();
}

void MainWindow::storeFrames(std::vector<QImage> images){
    frames=images;
}

void MainWindow::animate(){
    if((int)frames.size()==0){

    }else{
        if(currentFrame>(int)frames.size()-1){
            currentFrame=0;
        }
        ui->animation->setPixmap(QPixmap::fromImage(frames.at(currentFrame).scaled(ui->animation->width(),ui->animation->height())));
        currentFrame++;
        timer.start(frameTime*2);
    }
}

void MainWindow::onNewButtonPressed()
{
    QObjectList children = ui->scrollAreaContents->children();
    int index = children.size() - 1;
    while (index > 1) {
        QPushButton *c = qobject_cast<QPushButton*>(children[index]);
        ui->scrollFrameBox->removeWidget(c);
        delete c;
        QObject::disconnect(qobject_cast<QPushButton*>(ui->scrollAreaContents->children().last()), &QPushButton::clicked, m->a.frames.back(), &Frame::frameButtonPressed);
        QObject::disconnect(m->a.frames.back(), &Frame::changeFrame, m, &Model::switchFrame);
        ui->scrollFrameBox->update();
        index--;
    }
    emit createNewSprite();
    ui->canvas->updateGridSize32();

}

void MainWindow::loadPressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Sprite Animations (*.ssp)"));
    m->loadPressed(fileName);
    QWidget::update();

}

void MainWindow::updateFps(int i)
{
    frameTime=82-i;
}

void MainWindow::helpClicked()
{
    QString tips = "Here are some useful tips/notes about our sprite editor:\n\n"
                   "When changing the sprite size, it will clear the images on all frames/layers.\n"
                   "When removing a frame it will only remove the most recently added frame. And it will never remove the first frame.\n\n"
                   "Keyboard Shortcuts:\n"
                   "Draw: Ctrl+D\n"
                   "Erase: Ctrl+E\n"
                   "Spray Paint: Ctrl+Shift+D\n"
                   "Save: Ctrl+S\n"
                   "New: Ctrl+N\n"
                   "Load: Ctrl+L\n"
                   "Help: Ctrl+H\n"
                   "draw Circle: Ctrl+C\n"
                   "draw Square: Ctrl+R";

    QMessageBox helpBox;
    helpBox.setWindowTitle("Help");
    helpBox.setText(tips);
    helpBox.addButton(QMessageBox::Ok);
    helpBox.exec();
}

void MainWindow::changeUsingLayerText(QString text)
{
    ui->whichLayer->setText(text);
}

void MainWindow::saveDialog()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "Sprite Animations (*.json)");
    if (!filePath.isEmpty())
        m->savePressed(filePath);

}

void MainWindow::changeToLoadSize(int size)
{
    switch (size) {
    case 16:
        ui->canvas->updateGridSize16();
        break;
    case 32:
        ui->canvas->updateGridSize32();
        break;
    case 64:
        ui->canvas->updateGridSize64();
        break;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
