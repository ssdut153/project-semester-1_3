#ifndef UUMESSAGE_H
#define UUMESSAGE_H

#include "stdafx.h"
#include "message.h"

class uuMessage : public Message
{
public:
    uuMessage();
    uuMessage(QString fromUserName,QString toUserName);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString fromuser;
    QString touser;
};

#endif // UUMESSAGE_H
