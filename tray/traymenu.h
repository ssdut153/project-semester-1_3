#ifndef TRAYMENU_H
#define TRAYMENU_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"

class TrayMenu : public QMenu
{
    Q_OBJECT

private:
    QAction *exitAction;

public:
    explicit TrayMenu(QWidget *parent = 0);
    ~TrayMenu();

protected:

private slots:
    void on_exitAction_triggered();

};

#endif // TRAYMENU_H
