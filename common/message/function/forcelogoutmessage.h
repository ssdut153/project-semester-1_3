#ifndef FORCELOGOUTMESSAGE_H
#define FORCELOGOUTMESSAGE_H
#include "stdafx.h"
#include "../base/usernamemessage.h"

class forceLogoutMessage : public usernameMessage
{
public:
    forceLogoutMessage();
    forceLogoutMessage(QString username);
};

#endif // FORCELOGOUTMESSAGE_H
