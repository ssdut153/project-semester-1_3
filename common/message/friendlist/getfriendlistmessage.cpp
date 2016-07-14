#include "getfriendlistmessage.h"

getFriendListMessage::getFriendListMessage(QString username)
{
    user = username;
    head = "getFriendList";
}

getFriendListMessage::getFriendListMessage()
{
    head = "getFriendList";
}
