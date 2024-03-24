#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"

MainWindow::MainWindow(model& m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Canvas->setGridSize(32);
    QObject::connect(ui->Canvas,
            &Canvas::gridClicked,
            &m.pen,
            &Draw::drawImage);

    connect(m.f,
            &Frame::updateImage,
            &ui->Canvas,
            &Canvas::updateCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
