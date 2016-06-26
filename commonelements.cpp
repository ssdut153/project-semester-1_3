#include "commonelements.h"
#include "helper.h"

CommonElements::CommonElements(QObject *parent):
    QObject(parent),
    trayIcon(new TrayIcon),
    client(0),
    username(""),
    loginWindow(0),
    mainWindow(0),
    login(false),
    application(0)
{

}

CommonElements::~CommonElements()
{
    trayIcon->hide();
    delete trayIcon;
    delete client;
}

void CommonElements::connectServer()
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("103.13.222.121"), 6665);
    CommonElements *ce = CommonElements::getInstance();
    ce->client->waitForConnected();
    Helper *helper = Helper::getInstance();
    helper->connectServer();
}

void CommonElements::disconnectServer()
{
    Helper::getInstance()->disconnectServer();
    delete client;
    client = 0;
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
