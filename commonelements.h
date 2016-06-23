#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include "stdafx.h"
#include <QtNetwork>
#include "tray/trayicon.h"

class CommonElements:public QObject
{

private:
    static CommonElements *instance;
    explicit CommonElements(QObject *parent = 0);

public:
    ~CommonElements();
    TrayIcon *trayIcon;
    QTcpSocket *client;
    static CommonElements *getInstance();
    std::string username;
    bool login;
    QApplication *a;
};

#endif // COMMONELEMENTS_H
