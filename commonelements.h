#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include "stdafx.h"
#include <QtNetwork>
#include "tray/trayicon.h"

class CommonElements:public QObject
{

private:
    static CommonElements *instance;
    CommonElements(QObject *parent = 0);

public:
    ~CommonElements();
    TrayIcon *trayIcon;
    QTcpSocket *client;
    static CommonElements *getInstance();

};

#endif // COMMONELEMENTS_H
