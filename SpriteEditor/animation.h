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
    void addFrame(Frame *frame);
    void deleteFrame(Frame *frame);
    void setfps(int);
    void loadFile(std::string file);
    void saveFile(std::string file);
    void setImage();

private:
    std::vector<Frame*> frames;
    int fps;
    int currentFrame=0;
    std::string savedFile;
};

#endif // ANIMATION_H
