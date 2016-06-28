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
    friendName(item->text().left(item->text().size() - 4).toStdString()),
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
        p2pMessage pm(this->username, this->friendName.substr(0, this->friendName.size() - 8), message.toStdString());
        Helper *helper = Helper::getInstance();
        helper->writeClient(pm);
        ui->sendEdit->clear();
        ui->messageEdit->append(QString(this->username.c_str()) + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ui->messageEdit->append(message);
    }
}

void ChatWindow::appendText(QString time, QString content)
{
    ui->messageEdit->append(QString(this->friendName.c_str()) + " " + time);
    ui->messageEdit->append(content);
}

void ChatWindow::sendFail()
{
    ui->messageEdit->append("发送失败");
}

void ChatWindow::closeEvent(QCloseEvent */*event*/)
{
    parent->chatWindows.remove(this->item);
    delete this;
}
//{"head":"p2p","fromusername":"testuser1","tousername":"testuser2","createtime":"2000-10-10 12:12:12","content":"abcde"}
