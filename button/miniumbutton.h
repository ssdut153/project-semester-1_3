#ifndef MINIUMBUTTON_H
#define MINIUMBUTTON_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"

class MiniumButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MiniumButton(QWidget *parent = nullptr);

};

#endif // MINIUMBUTTON_H
