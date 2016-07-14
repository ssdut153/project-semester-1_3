#ifndef REQUESTFRIENDMESSAGE_H
#define REQUESTFRIENDMESSAGE_H
#include "stdafx.h"
#include "../base/uumessage.h"

class requestFriendMessage : public uuMessage
{
public:
    requestFriendMessage();
    requestFriendMessage(QString fromUserName, QString toUserName);
};

#endif // REQUESTFRIENDMESSAGE_H
