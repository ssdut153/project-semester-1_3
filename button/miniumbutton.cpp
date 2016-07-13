#include "miniumbutton.h"

MiniumButton::MiniumButton(QWidget *parent) :
    QPushButton(parent)
{

    this->setStyleSheet("QPushButton{border-image:url(:/images/minButton_0);}"
                        "QPushButton:hover{border-image:url(:/images/minButton_1);}"
                        "QPushButton:pressed{border-image:url(:/images/minButton_2);}");

    this->setFocusPolicy(Qt::ClickFocus);

}
