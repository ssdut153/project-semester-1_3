/*****************************************************************************************
 *  Copyright(c) 2016 Huwenqiang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-22
 *  作者: Hu Wenqiang
 *  说明:
 *
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#include "commonelements.h"
#include "helper.h"
/**
 * @brief CommonElements::CommonElements
 * @param parent 父级元素
 */
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

/**
 * @brief CommonElements::~CommonElements
 */
CommonElements::~CommonElements()
{
    trayIcon->hide();
    delete trayIcon;
    delete client;
}

/**
 * @brief CommonElements::connectServer
 */
void CommonElements::connectServer()
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("103.13.222.121"), 6665);
    CommonElements *ce = CommonElements::getInstance();
    ce->client->waitForConnected();
    Helper *helper = Helper::getInstance();
    helper->connectServer();
}
/**
 * @brief CommonElements::disconnectServer
 */
void CommonElements::disconnectServer()
{
    Helper::getInstance()->disconnectServer();
    delete client;
    client = 0;
}
/**
 * @brief CommonElements::instance
 */
CommonElements *CommonElements::instance = 0;
/**
 * @brief CommonElements::getInstance
 * @return CommonElements *
 */
CommonElements *CommonElements::getInstance()
{
    if(instance == 0)
    {
        instance = new CommonElements;
    }
    return instance;
}
