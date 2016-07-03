#ifndef ADDFRIENDMESSAGE_H
#define ADDFRIENDMESSAGE_H
#include "stdafx.h"
#include "../base/uumessage.h"

class addFriendMessage : public uuMessage
{
public:
    addFriendMessage();
    addFriendMessage(QString fromUserName,QString toUserName);
};

#endif // ADDFRIENDMESSAGE_H
