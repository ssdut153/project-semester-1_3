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

QString feedBackMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    jsonObject.insert("status", stat);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    return QString(byteArray);
}

bool feedBackMessage::loadfromJson(QString textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson.toStdString().c_str(), &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
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
    return true;
}
