#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"
#include <QLabel>
#include <QFile>

/// \brief Animation - a class for managing animation sequences
/// Inherits from QLabel to display the animation
class Animation : public QLabel
{
    Q_OBJECT
public:
    /// \brief fps - frames per second for the animation
    int fps;

    /// \brief frames - a vector storing pointers to the frames of the animation
    std::vector<Frame*> frames;

    /// \brief Animation constructor
    /// \param parent the parent widget, default is nullptr
    explicit Animation(QWidget *parent = nullptr);

    /// \brief addFrame - adds a frame to the animation sequence
    /// \param frame pointer to the frame to be added
    void addFrame(Frame* frame);

    /// \brief deleteFrame - removes a frame from the animation sequence
    /// \param frame pointer to the frame to be removed
    void deleteFrame();

    /// \brief setfps - sets the frames per second for the animation
    /// \param fps number of frames per second
    void setfps(int);

    /// \brief setImage - updates the image displayed by QLabel to the current frame
    void setImage();

    /// \brief file - stores file paths related to the animation
    QStringList file;

private:
    /// \brief currentFrame - index of the current frame in the animation sequence
    int currentFrame = 0;

    /// \brief savedFile - stores the file path of the saved animation
    std::string savedFile;
};


#endif // ANIMATION_H
