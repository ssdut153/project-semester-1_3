#ifndef SEARCHUSERMESSAGE_H
#define SEARCHUSERMESSAGE_H

#include "stdafx.h"
#include "../base/usernamemessage.h"

class searchUserMessage : public usernameMessage
{
public:
    searchUserMessage();
    searchUserMessage(QString username);
};

#endif // SEARCHUSERMESSAGE_H
