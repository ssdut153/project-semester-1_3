#ifndef EXITMESSAGEBOX_H
#define EXITMESSAGEBOX_H

#include "stdafx.h"

class ExitMessageBox:public QMessageBox
{
public:
    explicit ExitMessageBox(QWidget *parent = 0);
    ~ExitMessageBox();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *paintevent);

private:
    QImage *imp;
    bool pressed;
    QPoint place;
};

#endif // EXITMESSAGEBOX_H
