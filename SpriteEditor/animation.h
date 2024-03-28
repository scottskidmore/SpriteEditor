#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"
#include <QLabel>
#include <QFile>

class Animation : public QLabel
{
    Q_OBJECT
public:
    explicit Animation(QWidget *parent = nullptr);
    void addFrame(Frame* frame);
    void deleteFrame(Frame* frame);
    void setfps(int);
    void setImage();
    std::vector<Frame*> frames;
    int fps;

private:
    //int fps;
    int currentFrame=0;
    std::string savedFile;
};

#endif // ANIMATION_H
