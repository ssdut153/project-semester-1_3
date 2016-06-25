#ifndef HELPER_H
#define HELPER_H

#include "stdafx.h"
#include <string>
#include "common/cJSON.h"
#include "common/message/base/message.h"

class Helper:public QObject
{
    Q_OBJECT

private:
    explicit Helper();
    static Helper *helper;
    QString status;

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
