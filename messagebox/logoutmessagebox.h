#ifndef LOGOUTMESSAGEBOX_H
#define LOGOUTMESSAGEBOX_H

#include "stdafx.h"
#include "classes.h"

class LogoutMessageBox:public QMessageBox
{

public:
    explicit LogoutMessageBox(QWidget *parent = 0);
    ~LogoutMessageBox();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool pressed;
    QPoint place;

};

#endif // LOGOUTMESSAGEBOX_H
