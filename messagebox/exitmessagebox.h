#ifndef EXITMESSAGEBOX_H
#define EXITMESSAGEBOX_H

#include "stdafx.h"

class ExitMessageBox:public QMessageBox
{
public:
    explicit ExitMessageBox(QWidget *parent = 0);
    ~ExitMessageBox();
};

#endif // EXITMESSAGEBOX_H
