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
    void loadFile(std::string file);
    void saveFile(std::string file);

private:
    std::list<Frame> frames;
    int fps;
    std::string savedFile;
};

#endif // ANIMATION_H
