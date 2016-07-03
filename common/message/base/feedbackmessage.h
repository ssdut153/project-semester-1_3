#ifndef FEEDBACKMESSAGE_H
#define FEEDBACKMESSAGE_H

#include "stdafx.h"
#include "message.h"

class feedBackMessage : public Message
{
public:
    feedBackMessage();
    feedBackMessage(QString username,QString status);
    QString getJsonString();
    bool loadfromJson(QString textJson);
    QString user;
    QString stat;
};

#endif // FEEDBACKMESSAGE_H
