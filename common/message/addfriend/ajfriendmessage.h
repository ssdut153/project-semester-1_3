/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: ajfriendmessage.h
 *  简要描述:
 *
 *  创建日期:
 *  作者:
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#ifndef AJFRIENDMESSAGE_H
#define AJFRIENDMESSAGE_H
#include "stdafx.h"
#include "../base/message.h"

class ajFriendMessage : public Message
{
public:
    ajFriendMessage();
    ajFriendMessage(QString fromUserName, QString toUserName, QString accept);
    QString getJsonString();
    bool loadfromJson(QString textJson);
    QString fromuser;
    QString touser;
    QString acpt;
};

#endif // AJFRIENDMESSAGE_H
