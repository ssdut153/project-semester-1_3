#include "addfriendmessage.h"

addFriendMessage::addFriendMessage()
{
    head="addFriend";
}

addFriendMessage::addFriendMessage(QString fromUserName, QString toUserName)
{
    fromuser = fromUserName;
    touser = toUserName;
    head = "addFriend";
}
