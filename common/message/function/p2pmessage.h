#ifndef P2PMESSAGE_H
#define P2PMESSAGE_H

#include "../base/message.h"
#include "stdafx.h"

class p2pMessage : public Message
{
public:
    p2pMessage();
    p2pMessage(QString from, QString to, QString text);
    QString getJsonString();
    bool loadfromJson(QString textJson);
    QString FromUserName;
    QString ToUserName;
    QString CreateTime;
    QString Content;
};

#endif // P2PMESSAGE_H
