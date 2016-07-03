#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "regwindow.h"
#include "groupbox/logingroupbox.h"
#include "groupbox/waitinggroupbox.h"

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

signals:

private:
    LoginGroupBox *loginGroupBox;
    WaitingGroupBox *waitingGroupBox;


};

#endif // LOGINWINDOW_H
