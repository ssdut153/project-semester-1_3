#ifndef HELPER_H
#define HELPER_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"

class Helper:public QObject
{
    Q_OBJECT

private:
    explicit Helper();
    static Helper *helper;

private slots:
    void readClient();
public:
    ~Helper();
    static Helper *getInstance();
    QString getfromJson(QByteArray textJson, QString name);
    void writeClient(Message &message);
    QTcpSocket *client;
    void connectServer();
    void disconnectServer();
    void quit();

};

#endif // HELPER_H
