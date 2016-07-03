#include "usernamemessage.h"

usernameMessage::usernameMessage(QString username)
{
    user = username;
    head = "defaultUsername";
}

usernameMessage::usernameMessage()
{
    head = "defaultUsername";
}

QString usernameMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    return byteArray;
}
/**
 * @brief usernameMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool usernameMessage::loadfromJson(QString textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson.toStdString().c_str(), &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
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
    }
    else
    {
        return false;
    }
    return true;
}

