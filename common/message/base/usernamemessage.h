#ifndef USERNAMEMESSAGE_H
#define USERNAMEMESSAGE_H

#include "message.h"
#include "stdafx.h"

class usernameMessage : public Message
{
public:
    usernameMessage();
    usernameMessage(QString username);
    QString getJsonString();
    bool loadfromJson(QString textJson);
    QString user;
};

#endif // USERNAMEMESSAGE_H
