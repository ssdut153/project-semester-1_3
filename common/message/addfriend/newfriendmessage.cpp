#include "newfriendmessage.h"

newFriendMessage::newFriendMessage()
{
    head="newFriend";
}

newFriendMessage::newFriendMessage(QString username, int stat)
{
    user = username;
    head = "newFriend";
    status = stat;
}

QByteArray newFriendMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    jsonObject.insert("status", status);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool newFriendMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject  = jsonDocument.object();
            if(jsonObject.contains("username"))
            {
                QJsonValue jsonValue = jsonObject.take("username");
                if(jsonValue.isString())
                {
                    user = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            if(jsonObject.contains("status"))
            {
                QJsonValue jsonValue = jsonObject.take("status");
                if(jsonValue.isDouble())
                {
                    status = jsonValue.toInt();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
