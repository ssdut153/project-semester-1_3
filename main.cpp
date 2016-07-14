#include "stdafx.h"
#include "window/loginwindow.h"
#include "commonelements.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CommonElements *ce = CommonElements::getInstance();

    ce->setApplication(&a);

    ce->getTrayIcon()->show();

    LoginWindow *lw = new LoginWindow;
    ce->setLoginWindow(lw);
    lw->show();
//    lw->getLoginGroupBox()->getUsernameEdit()->setFocus();

    int r = a.exec();

    delete CommonElements::getInstance();

    delete Helper::getInstance();

    return r;

}
