#ifndef REGUSERMESSAGE_H
#define REGUSERMESSAGE_H

#include "stdafx.h"
#include "common/message/base/upmessage.h"

class regUserMessage : public upMessage
{
public:
    regUserMessage();
    regUserMessage(QString username, QString password);
};

#endif // REGUSERMESSAGE_H
