#ifndef TRAYMENU_H
#define TRAYMENU_H

#include "ui.h"
#include "stdafx.h"

class TrayMenu : public QMenu
{
    Q_OBJECT

private:
    QAction *exitAction;

public:
    explicit TrayMenu(QWidget *parent = 0);
    ~TrayMenu();
private slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // TRAYMENU_H
