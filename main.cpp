#include "stdafx.h"
#include "window/mainwindow.h"
#include "window/loginwindow.h"
#include "tray/traymenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    LoginWindow *w1 = new LoginWindow;
    w1->show();
    MainWindow *w2 = 0;

    QSystemTrayIcon *qsti = new QSystemTrayIcon;
    qsti->setToolTip("聊天工具");
    qsti->setIcon(QIcon(":/images/icon"));

    TrayMenu *trmn = new TrayMenu;

    qsti->setContextMenu(trmn);

    qsti->show();

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
