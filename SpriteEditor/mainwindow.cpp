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

    QObject::connect(&m->f,
            &Frame::updateImage,
            ui->canvas,
            &Canvas::updateCanvas);

    QObject::connect(ui->ActionDraw,
            &QAction::triggered,
            m,
            &model::drawPressed);

    QObject::connect(ui->actionSquare,
                     &QAction::triggered,
                     m,
                     &model::squarePressed);

    QObject::connect(ui->actionCircle,
                     &QAction::triggered,
                     m,
                     &model::circlePressed);


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

    QObject::connect(&m->f,
                     &Frame::updateImage,
                     this,
                     &MainWindow::updateFrameDisplay);

    QObject::connect(ui->layer1,
                     &QPushButton::clicked,
                     m,
                     &model::layer1);

    QObject::connect(ui->layer2,
                     &QPushButton::clicked,
                     m,
                     &model::layer2);

    QObject::connect(ui->layer3,
                     &QPushButton::clicked,
                     m,
                     &model::layer3);

    QObject::connect(ui->layer4,
                     &QPushButton::clicked,
                     m,
                     &model::layer4);

    QObject::connect(ui->layer5,
                     &QPushButton::clicked,
                     m,
                     &model::layer5);



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
                     &m->f,
                     &Frame::updateImageSize16);

    QObject::connect(ui->size32,
                     &QPushButton::clicked,
                     &m->f,
                     &Frame::updateImageSize32);

    QObject::connect(ui->size64,
                     &QPushButton::clicked,
                     &m->f,
                     &Frame::updateImageSize64);



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

MainWindow::~MainWindow()
{
    delete ui;
}
