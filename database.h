#ifndef DATABASE_H
#define DATABASE_H

#include "stdafx.h"
#include "classes.h"

class Database : public QObject
{
    Q_OBJECT

public:
    static Database *getInstance(QString username);
    bool createFriendTable(QString friendName);
    bool createFriendTables(QMap<QString, int> &friendNames);
    bool addMessage(QString friendName, bool send, QString time, QString message);

private:
    static Database *instance;
    explicit Database(QString username, QObject *parent = 0);
    QSqlDatabase database;

private slots:

};

#endif // DATABASE_H
