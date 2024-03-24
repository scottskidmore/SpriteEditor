#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"
#include <list>
#include <QFile>

class Animation
{
public:
    Animation();
    void addFrame(Frame frame);
    void deleteFrame(Frame *frame);
    void setfps(int);
    void loadFile(QFile file);
    void saveFile(QFile file);

private:
    std::list<Frame> frames;
    int fps;
    QFile savedFile;
};

#endif // ANIMATION_H
