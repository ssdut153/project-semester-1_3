#include "forcelogoutmessage.h"

forceLogoutMessage::forceLogoutMessage(QString username)
{
    user=username;
    head="forceLogout";
}

forceLogoutMessage::forceLogoutMessage()
{
    head="forceLogout";
}
