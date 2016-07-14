#include "commonelements.h"
#include "helper.h"
#include "messages.h"

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
    delete trayIcon;
    if(login)
    {
        delete this->mainWindow;
    }
    else
    {
        delete this->loginWindow;
    }
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

QString CommonElements::getUsername()
{
    return this->username;
}

LoginWindow *CommonElements::getLoginWindow()
{
    return this->loginWindow;
}

MainWindow *CommonElements::getMainWindow()
{
    return this->mainWindow;
}

QApplication *CommonElements::getApplication()
{
    return this->application;
}

bool CommonElements::isLogin()
{
    return this->login;
}

TrayIcon *CommonElements::getTrayIcon()
{
    return this->trayIcon;
}

void CommonElements::setUsername(QString username)
{
    this->username = username;
}

void CommonElements::setLoginWindow(LoginWindow *loginWindow)
{
    this->loginWindow = loginWindow;
}

void CommonElements::setApplication(QApplication *application)
{
    this->application = application;
}
