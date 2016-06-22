#include "commonelements.h"

CommonElements::CommonElements(QObject *parent):
    QObject(parent),
    trayIcon(new TrayIcon),
    client(new QTcpSocket(this))
{
    client->connectToHost(QHostAddress("103.13.222.121"), 6665);
}

CommonElements::~CommonElements()
{
    trayIcon->hide();
    delete trayIcon;
    delete client;
}

CommonElements *CommonElements::instance = 0;

CommonElements *CommonElements::getInstance()
{
    if(instance == 0)
    {
        instance = new CommonElements;
    }
    return instance;
}
