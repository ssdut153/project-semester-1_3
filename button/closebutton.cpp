#include "closebutton.h"

CloseButton::CloseButton(QWidget *parent):
    QPushButton(parent)
{
    this->setStyleSheet("QPushButton{border-image:url(:/images/close_0);}"
                        "QPushButton:hover{border-image:url(:/images/close_2);}"
                        "QPushButton:pressed{border-image:url(:/images/close_3);}");
    this->setFocusPolicy(Qt::ClickFocus);
}
