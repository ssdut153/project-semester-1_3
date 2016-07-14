#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include "stdafx.h"
#include "common/message/base/upmessage.h"

class loginMessage:public upMessage
{
public:
    loginMessage();
    loginMessage(QString username,QString password);
};

#endif // LOGINMESSAGE_H
