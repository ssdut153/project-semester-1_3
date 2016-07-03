#include "regusermessage.h"

regUserMessage::regUserMessage(QString username, QString password)
{
    user = username;
    pass = password;
    head = "regUser";
}

regUserMessage::regUserMessage()
{
    head="regUser";
}
