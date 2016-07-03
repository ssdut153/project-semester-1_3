#ifndef MESSAGE_H
#define MESSAGE_H

#include "stdafx.h"

class Message
{
public:
    Message();
    Message(QString h);
    virtual ~Message();
    virtual QString getJsonString() = 0;
    virtual bool loadfromJson(QString textJson) = 0;
    void addHead(QString h);
    QString getHead();
    QString head;
};


#endif // MESSAGE_H
