#include "feedbackmessage.h"

feedBackMessage::feedBackMessage(QString username,QString status)
{
    user = username;
    stat = status;
    head = "defaultFeedBack";
}

feedBackMessage::feedBackMessage()
{
    head="defauleFeedBack";
}

QByteArray feedBackMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    jsonObject.insert("status", stat);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool feedBackMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {

            QJsonObject jsonObject = jsonDocument.object();
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
                if(jsonValue.isString())
                {
                    stat = jsonValue.toString();
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
