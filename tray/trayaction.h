#ifndef TRAYACTION_H
#define TRAYACTION_H

#include "../ui.h"
#include "../stdafx.h"

class TrayAction:public QAction
{
    Q_OBJECT
public:
    explicit TrayAction(QWidget *parent = 0);
    ~TrayAction();
};

#endif // TRAYACTION_H
