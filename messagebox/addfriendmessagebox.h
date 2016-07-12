#ifndef ADDFRIENDMESSAGEBOX_H
#define ADDFRIENDMESSAGEBOX_H

#include "stdafx.h"
#include "classes.h"

class AddFriendMessageBox:public QMessageBox
{
public:
    AddFriendMessageBox(QString friendName, QWidget *parent = 0);
    ~AddFriendMessageBox();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool pressed;
    QPoint place;

};

#endif // ADDFRIENDMESSAGEBOX_H
