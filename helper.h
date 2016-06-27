/*****************************************************************************************
 *  Copyright(c) 2016 Huwenqiang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-23
 *  作者: Hu Wenqiang
 *  说明:
 *
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#ifndef HELPER_H
#define HELPER_H

#include "stdafx.h"
#include <string>
#include "common/cJSON.h"
#include "common/message/base/message.h"

class Helper:public QObject
{
    Q_OBJECT

private:
    explicit Helper();
    static Helper *helper;
    QString status;

private slots:
    void readClient();

public:
    static Helper *getInstance();
    void writeClient(Message &message);
    QTcpSocket *client;
    void connectServer();
    void disconnectServer();
    void quit();

};

#endif // HELPER_H
