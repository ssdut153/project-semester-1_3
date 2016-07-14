#ifndef EXITMESSAGEBOX_H
#define EXITMESSAGEBOX_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"

class ExitMessageBox:public QMessageBox
{
    Q_OBJECT

public:
    explicit ExitMessageBox(QWidget *parent = 0);
    ~ExitMessageBox();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *paintevent);

private:
    bool pressed;
    QPoint place;

};

#endif // EXITMESSAGEBOX_H
