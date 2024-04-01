#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include <QRandomGenerator>
#include "qobject.h"

/// \brief Draw - a class for drawing with different tools and shapes
/// Inherits from QObject
class Draw : public QObject
{
    Q_OBJECT
public:
    /// \brief Draw constructor
    /// \param parent object defaulting to nullptr
    explicit Draw(QObject *parent = nullptr);
    // int getLineWdith();
    // void setLineWdith(int);
    // QColor getColor();
    /// \brief setColor sets the draw color
    /// \param QColor color to set
    void setColor(QColor);
    /// \brief drawSquare
    /// \param QPoint point to draw at
    /// \param int size of square
    void drawSquare(QPoint, int);
    /// \brief drawCircle
    /// \param QPoint point to draw at
    /// \param int size of circle
    void drawCircle(QPoint, int);
    //void drawTraingle(QPoint, int);
    /// \brief setImage sets this image to the provided image
    /// \param QImage& reference of image to set this
    void setImage(QImage&);
    /// \brief eraseTool sets the pixel at the point to transparent
    /// \param QPoint point to set
    void eraseTool(QPoint);
    /// \brief getImage getter for image
    /// \return pointer to image
    QImage getImage();
    /// \brief sprayPaint draws scattered pixels in the provided radius and density
    /// \param int radius
    /// \param int density
    void sprayPaint(QPoint, int, int);

private:
    /// \brief color current color
    QColor color;
    //int lineWidth;
    /// \brief image that is being drawn on
    QImage* image;

public slots:
    //void drawImage(QPoint);
    /// \brief drawPixel sets pixel at the provided point to the color
    /// \param QPoint point to draw at
    void drawPixel(QPoint);
signals:
    //void imageUpdated();
};

#endif // DRAW_H
