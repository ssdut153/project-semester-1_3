#ifndef NEWFRIENDMESSAGE_H
#define NEWFRIENDMESSAGE_H
#include "stdafx.h"
#include "../base/usernamemessage.h"

class newFriendMessage : public usernameMessage
{
public:
    newFriendMessage();
    newFriendMessage(QString username);
};

#endif // NEWFRIENDMESSAGE_H
