#include "logoutmessage.h"

logoutMessage::logoutMessage(QString username)
{
    user = username;
    head = "logout";
}

logoutMessage::logoutMessage()
{
    head = "logout";
}
