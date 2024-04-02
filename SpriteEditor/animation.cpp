#include "animation.h"

Animation::Animation(QWidget *parent)
    : QLabel{parent}
{

}
void Animation::addFrame(Frame *frame)
{
    frames.push_back(frame);

}

void Animation::deleteFrame()
{
    frames.pop_back();
}

void Animation::setfps(int rate)
{
    fps = rate;
}

void Animation::setImage()
{
    Frame* f = frames.at(currentFrame);
    QImage image = f->getCurrentLayer();
    QPixmap p = QPixmap::fromImage(image);
    this->setPixmap(p);
}
