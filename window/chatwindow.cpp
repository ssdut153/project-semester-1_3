#include "chatwindow.h"

ChatWindow::ChatWindow(std::string username, std::string friendName, QWidget *parent):
    QMainWindow(parent),
    username(username),
    friendName(friendName),
    messageEdit(new QTextEdit(this)),
    sendEdit(new QTextEdit(this)),
    sendButton(new QPushButton(this))
{
    this->setMinimumSize(800, 600);
    this->setMaximumSize(800, 600);

    this->setWindowTitle(friendName.c_str());

    this->messageEdit->setGeometry(20, 20, 760, 400);
    this->sendEdit->setGeometry(20, 430, 760, 120);
    this->sendButton->setGeometry(700, 560, 50, 30);

    this->sendButton->setText("发送");

    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(on_sendButton_clicked()));

}

ChatWindow::~ChatWindow()
{

}

void ChatWindow::on_sendButton_clicked()
{

}
