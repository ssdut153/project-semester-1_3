#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include "stdafx.h"
#include "classes.h"
#include "tray/trayicon.h"
#include "window/loginwindow.h"
#include "window/mainwindow.h"
#include "helper.h"

class CommonElements:public QObject
{
    Q_OBJECT

private:
    static CommonElements *instance;
    explicit CommonElements(QObject *parent = 0);
    friend class Helper;

public:
    ~CommonElements();
    TrayIcon *trayIcon;
    QTcpSocket *client;
    static CommonElements *getInstance();
    QString username;
    LoginWindow *loginWindow;
    MainWindow *mainWindow;
    bool login;
    QApplication *application;
    void connectServer();
    void disconnectServer();

};

#endif // COMMONELEMENTS_H
