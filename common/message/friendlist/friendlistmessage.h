#ifndef FRIENDLISTMESSAGE_H
#define FRIENDLISTMESSAGE_H

#include "../base/usernamemessage.h"
#include "stdafx.h"

class friendListMessage : public Message
{
public:
    friendListMessage();
    void adduser(QString username,int status);
    QString getJsonString();
    bool loadfromJson(QString textJson);
    QMap<QString, int> users;
    int size;
};

#endif // FRIENDLISTMESSAGE_H
