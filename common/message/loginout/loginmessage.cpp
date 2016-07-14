#include "loginmessage.h"

loginMessage::loginMessage(QString username,QString password)
{
    user = username;
    pass = password;
    head = "login";
}

loginMessage::loginMessage()
{
    head = "login";
}
