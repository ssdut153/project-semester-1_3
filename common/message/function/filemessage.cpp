#include "filemessage.h"

fileMessage::fileMessage()
{
    head = "file";
}

fileMessage::fileMessage(QString from, QString to, QString severName, QString formalName)
{
    head = "file";
    FromUserName = from;
    ToUserName = to;
    Content = formalName;
    CreateTime = severName;
}
