#include "searchusermessage.h"

searchUserMessage::searchUserMessage()
{
    head="searchUser";
}

searchUserMessage::searchUserMessage(QString username)
{
    user=username;
    head="searchUser";
}
