#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <QImageWriter>
#include <QFileDialog>

/// Reviewed by Scott Skidmore
/// \brief Canvas - a class for displaying sprites on the UI
/// Inherits from QLabel to display the sprite
class Canvas : public QLabel
{
    Q_OBJECT
public:
    /// \brief Canvas constructor
    /// \param parent the parent widget, default is nullptr
    explicit Canvas(QWidget *parent = nullptr);
    /// \brief setGridSize sets the size of the background grid
    /// \param size ex. 16, 32, 64
    void setGridSize(int size);
    /// \brief drawGrid draws the grid on the UI canvas
    void drawGrid();
    /// \brief layers vector storing the individual layers as QImages
    std::vector<QImage> layers;

//protected:
    /// \brief paintEvent event to capture drawing
    /// \param event sent by UI
    void paintEvent(QPaintEvent *event);
    /// \brief mouseMoveEvent event to capture mouse movement
    /// \param event sent by UI
    void mouseMoveEvent(QMouseEvent *event);
    /// \brief mousePressEvent event to capture mouse pressed
    /// \param event sent by UI
    void mousePressEvent(QMouseEvent *event);
    /// \brief mouseReleaseEvent event to capture mouse released
    /// \param event sent by UI
    void mouseReleaseEvent(QMouseEvent *event);

private:
    /// \brief gridSize size of grid on UI canvas
    int gridSize;
    /// \brief trackMouse bool to track when the mouse is being tracked
    bool trackMouse;
    /// \brief cellSize size of the cells
    int cellSize;
    /// \brief startPoint QPoint to store a mouse startpoint
    QPoint startPoint;
    /// \brief endPoint QPoint to store a moiuse endpoint
    QPoint endPoint;


signals:
    /// \brief gridClicked emitted when there is a mouse clicked event
    void gridClicked(QPoint);
    /// \brief drawingAction emitted when there is a drawing event
    /// \param startPoint taken from mouse pressed event
    /// \param endPoint taken from mouse released event
    void drawingAction(QPoint startPoint, QPoint endPoint);
public slots:
    /// \brief updateCanvas updates the UI canvas based on the sent vector of QImages
    void updateCanvas(std::vector<QImage>);
    /// \brief updateGridSize16 updates the UI grid size to 16x16
    void updateGridSizeTo16();
    /// \brief updateGridSize32 updates the UI grid size to 32x32
    void updateGridSizeTo32();
    /// \brief updateGridSize64 updates the UI grid size to 64x64
    void updateGridSizeTo64();
    /// \brief loadPressed displays the dialog box for file loading
    void loadPressed();
};

#endif // CANVAS_H
