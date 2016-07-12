#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "regwindow.h"
#include "groupbox/logingroupbox.h"
#include "groupbox/waitinggroupbox.h"
#include "button/closebutton.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    LoginGroupBox *getLoginGroupBox();
    WaitingGroupBox *getWaitingGroupBox();
    void loginFail();

protected:
    void closeEvent(QCloseEvent *event);

private:
    LoginGroupBox *loginGroupBox;
    WaitingGroupBox *waitingGroupBox;
    CloseButton *closeButton;

private slots:
    void on_closeButton_clicked();
};

#endif // LOGINWINDOW_H
