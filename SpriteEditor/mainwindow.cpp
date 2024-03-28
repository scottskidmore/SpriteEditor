#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

MainWindow::MainWindow(model *m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setGridSize(32);
    QObject::connect(ui->canvas,
            &Canvas::gridClicked,
            m,
            &model::editImage);

    QObject::connect(m->f,
            &Frame::updateImage,
            ui->canvas,
            &Canvas::updateCanvas);

    QObject::connect(ui->ActionDraw,
            &QAction::triggered,
            m,
            &model::drawPressed);

    QObject::connect(ui->actionErase,
            &QAction::triggered,
            m,
            &model::erasePressed);

    QObject::connect(ui->actionSave,
                     &QAction::triggered,
                     m,
                     &model::savePressed);


    QObject::connect(ui->chooseColor,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::chooseColor);

    QObject::connect(m,
                     &model::updateFrameDisplay,
                     this,
                     &MainWindow::updateFrameDisplay);

    QObject::connect(ui->addFrameButton,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::onAddFrame);

    QObject::connect(ui->frame0,
                     &QPushButton::clicked,
                     m->f,
                     &Frame::frameButtonPressed);

    QObject::connect(m->f,
                     &Frame::changeFrame,
                     m,
                     &model::switchFrame);

    QObject::connect(this,
                     &MainWindow::frameButtonAdded,
                     m,
                     &model::addFrame);

    QObject::connect(m,
                     &model::connectFrameButton,
                     this,
                     &MainWindow::connectButtonFrame);

    QObject::connect(m,
                     &model::connectFrameUpdate,
                     this,
                     &MainWindow::connectNewFrame);

    QObject::connect(ui->removeFrameButton,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::onRemoveFrame);
    QObject::connect(this,
                     &MainWindow::frameButtonRemoved,
                     m,
                     &model::deleteFrame);

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
    for (int i = 1; i <= images.size() && i < children.size(); i++) {
        QPushButton *c = qobject_cast<QPushButton*>(children[i]);
        QPixmap m;
        m.convertFromImage(images[i-1]);
        QIcon icon(m);
        c->setIcon(icon);
        c->setIconSize(m.rect().size());
    }
}

void MainWindow::connectButtonFrame()
{
    QObject::connect(qobject_cast<QPushButton*>(ui->scrollAreaContents->children().last()), &QPushButton::clicked, m->a.frames.back(), &Frame::frameButtonPressed);
    QObject::connect(m->a.frames.back(), &Frame::changeFrame, m, &model::switchFrame);
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

        emit frameButtonRemoved();
    }
    ui->canvas->update();
}


MainWindow::~MainWindow()
{
    delete ui;
}
