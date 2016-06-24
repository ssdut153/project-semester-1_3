#include "stdafx.h"
#include "window/loginwindow.h"
#include "commonelements.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    QApplication *a = new QApplication(argc, argv);

    CommonElements *ce = CommonElements::getInstance();

//    Helper::getInstance();

    ce->a = a;

    LoginWindow *lw = new LoginWindow;
    ce->loginWindow = lw;
    lw->show();

    ce->trayIcon->show();

    return a->exec();

}
