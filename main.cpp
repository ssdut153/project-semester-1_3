#include "stdafx.h"
#include "window/loginwindow.h"
#include "commonelements.h"
#include "helper.h"

int main(int argc, char *argv[])
{
    QApplication *a = new QApplication(argc, argv);

    CommonElements *ce = CommonElements::getInstance();

    Helper::getInstance();

    ce->a = a;

    LoginWindow *lw = new LoginWindow;
    ce->loginWindow = lw;
    lw->show();

    ce->trayIcon->show();

//    while(true)
//    {
//        QEventLoop eventloop;
//        QTimer::singleShot(50, &eventloop, SLOT(quit()));
//        eventloop.exec();
//        if(w1->isLogin())
//        {
//            w1->hide();
//            delete w1;

//            break;
//        }
//    }

    return a->exec();

}
