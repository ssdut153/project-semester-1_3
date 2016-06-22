#ifndef TRAYMENU_H
#define TRAYMENU_H

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
    void on_exitAction_triggered();
protected:
//    void paintEvent(QPaintEvent *event);
};

#endif // TRAYMENU_H
