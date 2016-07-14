#ifndef MESSAGE_H
#define MESSAGE_H

#include "stdafx.h"

class Message
{
public:
    Message();
    Message(QString h);
    virtual ~Message();
    virtual QByteArray getJsonString() = 0;
    virtual bool loadfromJson(QByteArray textJson) = 0;
    void addHead(QString h);
    QString getHead();
    QString head;
};


#endif // MESSAGE_H
