#ifndef GETFRIENDLISTMESSAGE_H
#define GETFRIENDLISTMESSAGE_H

#include "../base/usernamemessage.h"

class getFriendListMessage : public usernameMessage
{
public:
    getFriendListMessage();
    getFriendListMessage(QString username);
};

#endif // GETFRIENDLISTMESSAGE_H
