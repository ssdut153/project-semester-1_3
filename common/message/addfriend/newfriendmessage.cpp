#include "newfriendmessage.h"

newFriendMessage::newFriendMessage()
{
    head="newFriend";
}

newFriendMessage::newFriendMessage(QString username)
{
    user = username;
    head = "newFriend";
}
