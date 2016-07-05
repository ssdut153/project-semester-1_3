#ifndef FRIENDLISTMESSAGE_H
#define FRIENDLISTMESSAGE_H

#include "../base/usernamemessage.h"
#include "stdafx.h"

class friendListMessage : public Message
{
public:
    friendListMessage();
    void adduser(QString username,int status);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QMap<QString, int> users;
    int size;
};

#endif // FRIENDLISTMESSAGE_H
