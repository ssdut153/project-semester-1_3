#include "miniumbutton.h"

MiniumButton::MiniumButton(QWidget *parent) :
    QPushButton(parent)
{
    this->setIcon(QIcon(":/images/minButton"));
    this->setIconSize(QSize(30,30));
    this->setStyleSheet("background-color:rgba(0,0,0,0);");
    this->setFocusPolicy(Qt::ClickFocus);
}
