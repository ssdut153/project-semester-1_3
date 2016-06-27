#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/function/p2pmessage.h"

ChatWindow::ChatWindow(std::string username, std::string friendName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    username(username),
    friendName(friendName)
{
    ui->setupUi(this);
    this->setWindowTitle(friendName.c_str());
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_sendButton_clicked()
{
    QString message = ui->sendEdit->toPlainText();
    if(!(message == ""))
    {
        p2pMessage pm(this->username, this->friendName, message.toStdString());
        Helper *helper = Helper::getInstance();
        helper->writeClient(pm);
    }
}
