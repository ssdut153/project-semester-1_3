#include "stdafx.h"
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow *w1 = new LoginWindow;
    w1->show();

    MainWindow *w2 = new MainWindow;
    w2->show();

    return a.exec();
}
