#ifndef WAITINGGROUPBOX_H
#define WAITINGGROUPBOX_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "commonelements.h"
#include "helper.h"

class WaitingGroupBox:public QGroupBox
{
    Q_OBJECT

public:
    explicit WaitingGroupBox(QWidget *parent = 0);
    QPushButton *getCancelButton();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent */*event*/);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel *waitingLabel;
    QPushButton *cancelButton;
    bool pressed;
    QPoint place;

private slots:
    void on_cancelButton_clicked();

};

#endif // WAITINGGROUPBOX_H
