#include "stdafx.h"
#include "tray/trayicon.h"
#include "window/loginwindow.h"
#include "commonelements.h"

int main(int argc, char *argv[])
{
    QApplication *a = new QApplication(argc, argv);

    TrayIcon *ti = new TrayIcon;
    LoginWindow *lw = new LoginWindow;
    CommonElements *ce = CommonElements::getInstance();

    ce->trayIcon = ti;
    ce->application = a;
    ce->loginWindow = lw;

    ti->show();
    lw->show();
    return a->exec();
}
