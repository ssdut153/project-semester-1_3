#include "database.h"
#include "commonelements.h"

Database::Database(QString username, QObject *parent) :
    QObject(parent),
    database(QSqlDatabase::addDatabase("QSQLITE"))
{
    database.setDatabaseName(username);
    database.setUserName("root");
    database.setPassword("12345678");
    if(!database.open())
    {
        CommonElements *ce = CommonElements::getInstance();
        ce->getApplication()->quit();
    }
}

bool Database::createFriendTable(QString friendName)
{
    QString sql = QString("create table ") + friendName + "(messagetime datetime not null, send integer not null, message text not null)";
    QSqlQuery query;
//    query.prepare(sql);
//    query.addBindValue(friendName);
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
        qDebug()<<"存储记录成功";
        return true;
    }
    else
    {
        qDebug()<<"存储记录失败";
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
