#include "database.h"
#include "commonelements.h"

Database::Database(QString username, QObject *parent) :
    QObject(parent),
    database(QSqlDatabase::addDatabase("QSQLITE"))
{
    database.setDatabaseName(username);
    if(!database.open())
    {
//        CommonElements *ce = CommonElements::getInstance();
//        ce->getApplication()->quit();
    }
}

bool Database::createFriendTable(QString friendName)
{
    QString sql = QString("create table ") + friendName + "(messagetime datetime not null, send integer not null, message text not null)";
    QSqlQuery query;
    if(query.exec(sql))
    {
        return true;
    }
    else
    {
//        CommonElements *ce = CommonElements::getInstance();
//        ce->getApplication()->quit();
        return false;
    }
}

void Database::loadMessage(ChatWindow *chatWindow, QString friendName)
{
    QString sql = QString("select send, messagetime, message from ") + friendName + " order by messagetime asc";
    QSqlQuery query;
    if(query.exec(sql))
    {
        while(query.next())
        {
            QString str;
            int send = query.value(0).toInt();
            if(send == 0)
            {
                str = QString("<span style=\"color: green;\">") + friendName + "</span>";
            }
            else
            {
                QString username = CommonElements::getInstance()->getUsername();
                str = QString("<span style=\"color: blue;\">") + username + "</span>";
            }

            QString time = query.value(1).toString();
            str += " <span style=\"color:cyan\">" + time + "</span>";
            chatWindow->getMessageEdit()->append(str);
            QString content = query.value(2).toString();
            chatWindow->readContent(content);

        }
    }
}

bool Database::addMessage(QString friendName, bool send, QString time, QString message)
{
    QString sql = QString("insert into ") + friendName + "(messagetime, send, message) values(:time,:send,:message)";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":time", time);
    if(send)
    {
        query.bindValue(":send", 1);
    }
    else
    {
        query.bindValue(":send", 0);
    }
    query.bindValue(":message", message);
    if(query.exec())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Database::createFriendTables(QMap<QString, int> &friendNames)
{
    bool b = true;
    for(QMap<QString, int>::iterator it = friendNames.begin(); it != friendNames.end(); it++)
    {
        if(!createFriendTable(it.key()))
        {
            b = false;
        }
    }
    return b;
}

Database *Database::instance = 0;

Database *Database::getInstance(QString username)
{
    if(instance == 0)
    {
        instance = new Database(username);
    }
    return instance;
}
