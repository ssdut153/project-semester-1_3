#ifndef UPMESSAGE_H
#define UPMESSAGE_H

#include "message.h"
#include "stdafx.h"

class upMessage : public Message
{
public:
    upMessage();
    upMessage(QString username,QString password);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString user;
    QString pass;
};

#endif // UPMESSAGE_H
