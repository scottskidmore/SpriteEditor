#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

MainWindow::MainWindow(model &m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setGridSize(32);
    QObject::connect(ui->canvas,
            &Canvas::gridClicked,
            &m,
            &model::drawImage);

    QObject::connect(&m.f,
            &Frame::updateImage,
                     ui->canvas,
            &Canvas::updateCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
