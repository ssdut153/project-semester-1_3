#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(std::string username, std::string friendName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    username(username),
    friendName(friendName)
{
    ui->setupUi(this);
    this->setWindowTitle(username.c_str());
}

ChatWindow::~ChatWindow()
{
    delete ui;
}
