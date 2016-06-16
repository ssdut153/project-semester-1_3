#include "stdafx.h"
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow *w1 = new LoginWindow;
    w1->show();
    MainWindow *w2 = 0;

    while(true)
    {
        QEventLoop eventloop;
        QTimer::singleShot(50, &eventloop, SLOT(quit()));
        eventloop.exec();
        if(w1->isLogin())
        {
            w1->hide();
            delete w1;
            w2 = new MainWindow;
            w2->show();
            break;
        }
    }

    return a.exec();
}
