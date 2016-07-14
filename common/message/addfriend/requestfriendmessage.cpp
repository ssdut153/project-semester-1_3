#include "requestfriendmessage.h"

requestFriendMessage::requestFriendMessage()
{
    head="requestFriend";
}

requestFriendMessage::requestFriendMessage(QString fromUserName, QString toUserName)
{
    fromuser = fromUserName;
    touser = toUserName;
    head = "requestFriend";
}
