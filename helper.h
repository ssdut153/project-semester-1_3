#ifndef HELPER_H
#define HELPER_H

#include "stdafx.h"
#include <string>
#include "cJSON.h"
#include "message/message.h"

class Helper:public QObject
{
    Q_OBJECT

private:
    explicit Helper();
    static Helper *helper;

private slots:
    void readClient();

public:
    static Helper *getInstance();
    std::string getfromJson(std::string textJson, const char *name);
    void writeClient(Message &message);
    QTcpSocket *client;
    void connectServer();
    void disconnectServer();

};

#endif // HELPER_H
