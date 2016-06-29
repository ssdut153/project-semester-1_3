/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: feedbackmessage.h
 *  简要描述:
 *
 *  创建日期: 2016-6-25
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "feedbackmessage.h"
/**
 * @brief feedBackMessage::feedBackMessage
 * @param username 用户名
 * @param status 状态
 */
feedBackMessage::feedBackMessage(QString username,QString status)
{
    user = username;
    stat = status;
    head = "defaultFeedBack";
}
/**
 * @brief feedBackMessage::feedBackMessage
 */
feedBackMessage::feedBackMessage()
{
    head="defauleFeedBack";
}
/**
 * @brief feedBackMessage::getJsonString
 * @return std::string 对应的单行Json字符串
 */
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
/**
 * @brief feedBackMessage::loadfromJson
 * @param textJson Json字符串
 * @return bool 是否载入成功
 */
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
