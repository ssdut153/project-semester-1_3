#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/function/p2pmessage.h"

ChatWindow::ChatWindow(std::string username, QListWidgetItem *item, MainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow),
    username(username),
    item(item),
    friendName(item->text().toStdString()),
    parent(parent)
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
        ui->sendEdit->clear();
        ui->messageEdit->append(message);
    }
}

void ChatWindow::closeEvent(QCloseEvent */*event*/)
{
    parent->chatWindows.remove(this->item);
    delete this;
}
