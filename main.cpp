#include "stdafx.h"
#include "window/loginwindow.h"
#include "commonelements.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    LoginWindow *w1 = new LoginWindow;
    w1->show();

    CommonElements *ce = CommonElements::getInstance();
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

    return a.exec();

}
