#ifndef LOGOUTMESSAGE_H
#define LOGOUTMESSAGE_H

#include "stdafx.h"
#include "common/message/base/usernamemessage.h"

class logoutMessage : public usernameMessage
{
public:
    logoutMessage();
    logoutMessage(QString username);
};

#endif // LOGOUTMESSAGE_H
