#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include "stdafx.h"
#include "tray/trayicon.h"
#include "window/loginwindow.h"
#include "window/mainwindow.h"

class LoginWindow;

class CommonElements:public QObject
{
    Q_OBJECT

private:
    static CommonElements *instance;
    explicit CommonElements(QObject *parent = 0);

public:
    ~CommonElements();
    TrayIcon *trayIcon;
    QTcpSocket *client;
    static CommonElements *getInstance();
    std::string username;
    LoginWindow *loginWindow;
    MainWindow *mainWindow;
    bool login;
    QApplication *application;
    void connectServer();
    void disconnectServer();

};

#endif // COMMONELEMENTS_H
