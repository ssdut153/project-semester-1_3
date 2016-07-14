#ifndef NEWFRIENDMESSAGE_H
#define NEWFRIENDMESSAGE_H

#include "../base/usernamemessage.h"

class newFriendMessage : public usernameMessage
{
public:
    newFriendMessage();
    newFriendMessage(QString username, int stat);
    QByteArray getJsonString();
    bool loadfromJson(QByteArray textJson);
    int status;
};

#endif // NEWFRIENDMESSAGE_H
