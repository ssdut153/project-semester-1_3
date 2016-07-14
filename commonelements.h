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
    TrayIcon *trayIcon;
    QTcpSocket *client;
    QString username;
    LoginWindow *loginWindow;
    MainWindow *mainWindow;
    bool login;
    QApplication *application;

public:
    ~CommonElements();
    static CommonElements *getInstance();
    void connectServer();
    void disconnectServer();

    TrayIcon *getTrayIcon();
    QString getUsername();
    LoginWindow *getLoginWindow();
    MainWindow *getMainWindow();
    QApplication *getApplication();
    bool isLogin();

    void setUsername(QString username);

    void setLoginWindow(LoginWindow *loginWindow);
    void setApplication(QApplication *application);

};

#endif // COMMONELEMENTS_H
