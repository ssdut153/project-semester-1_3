#ifndef AJFRIENDMESSAGE_H
#define AJFRIENDMESSAGE_H
#include "stdafx.h"
#include "../base/message.h"

class ajFriendMessage : public Message
{
public:
    ajFriendMessage();
    ajFriendMessage(QString fromUserName, QString toUserName, QString accept);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    QString fromuser;
    QString touser;
    QString acpt;
};

#endif // AJFRIENDMESSAGE_H
