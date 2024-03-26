#include "animation.h"

Animation::Animation(QWidget *parent)
    : QLabel{parent}
{

}
void Animation::addFrame(Frame *frame)
{
    frames.push_back(frame);

}

void Animation::deleteFrame(Frame *frame)
{

}

void Animation::setfps(int)
{

}

void Animation::loadFile(std::string file)
{

}

void Animation::saveFile(std::string file)
{

}
void Animation::setImage()
{
    Frame* f = frames.at(currentFrame);
    QImage image = f->getCurrentLayer();
    QPixmap p = QPixmap::fromImage(image);
    this->setPixmap(p);
}
