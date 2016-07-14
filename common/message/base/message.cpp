#include "message.h"

Message::Message()
{
    head = "default";
}

Message::Message(QString h)
{
    head = h;
}

Message::~Message()
{

}

void Message::addHead(QString h)
{
    head = h;
}

QString Message::getHead()
{
    return head;
}

