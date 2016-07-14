#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"

class CloseButton:public QPushButton
{
    Q_OBJECT

public:
    explicit CloseButton(QWidget *parent = 0);

};

#endif // CLOSEBUTTON_H
