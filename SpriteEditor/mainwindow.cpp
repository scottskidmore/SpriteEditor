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


    m->setDrawLayer();
}


void MainWindow::chooseColor() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        ui->colorLabel->setStyleSheet("background-color: " + color.name() + ";");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
