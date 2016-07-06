#include "friendlistmessage.h"

void friendListMessage::adduser(QString username, int status)
{
    users.insert(username, status);
    size++;
}

friendListMessage::friendListMessage()
{
    head = "friendList";
    size = 0;
}

QByteArray friendListMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    QJsonArray jsonArray;
    for(QMap<QString, int>::iterator it = users.begin();it != users.end();it++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("username", it.key());
        jsonObject.insert("status", it.value());
        jsonArray.push_back(jsonObject);
    }
    jsonObject.insert("friendlist", jsonArray);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool friendListMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("friendlist"))
            {
                QJsonValue friendListValue = jsonObject.take("friendlist");
                if(friendListValue.isArray())
                {
                    QJsonArray jsonArray = friendListValue.toArray();
                    size = jsonArray.size();
                    for(int i = 0;i < size;i++)
                    {
                        QJsonValue jsonValue = jsonArray.at(i);
                        if(jsonValue.isObject())
                        {
                            QJsonObject tempJsonObject =jsonValue.toObject();
                            if(tempJsonObject.contains("username") && tempJsonObject.contains("status"))
                            {
                                QJsonValue usernameValue = tempJsonObject.take("username");
                                QJsonValue statusValue = tempJsonObject.take("status");
                                if(usernameValue.isString() && statusValue.isDouble())
                                {
                                    users.insert(usernameValue.toString(), statusValue.toInt());
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
