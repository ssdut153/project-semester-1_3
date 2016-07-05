#include "chatwindow.h"
#include "commonelements.h"
#include "helper.h"
#include "common/message/function/p2pmessage.h"
#include "database.h"

ChatWindow::ChatWindow(QListWidgetItem *item, MainWindow *parent) :
    QMainWindow(parent),
    username(CommonElements::getInstance()->getUsername()),
    item(item),
    friendName(item->text().left(item->text().size() - 4)),
    messageEdit(new QTextEdit(this)),
    sendEdit(new QTextEdit(this)),
    sendButton(new QPushButton(this))
{
    this->setMinimumSize(800, 600);
    this->setMaximumSize(800, 600);

    this->setWindowTitle(this->friendName);

    this->sendButton->setText("发送");

    this->messageEdit->setReadOnly(true);

    this->messageEdit->setGeometry(25, 20, 750, 380);
    this->sendEdit->setGeometry(25, 420, 750, 120);
    this->sendButton->setGeometry(710, 550, 60, 30);

    connect(this->sendButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked()));

}

QTextEdit *ChatWindow::getMessageEdit()
{
    return this->messageEdit;
}

void ChatWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    CommonElements *ce = CommonElements::getInstance();
    ce->getMainWindow()->getChatWindows().remove(this->item);
    delete this;
}

void ChatWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        this->on_sendButton_clicked();
        break;
    }
}

void ChatWindow::on_sendButton_clicked()
{
    QString content = this->sendEdit->toPlainText();
    if(content != "")
    {
        p2pMessage pm(this->username, this->friendName, content);
        Helper *helper = Helper::getInstance();
        helper->writeClient(pm);
        this->sendEdit->clear();
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        this->messageEdit->append(this->username + " " + time);
        this->messageEdit->append(content);
        Database *db = Database::getInstance(this->username);
        db->addMessage(this->friendName, 1, time, content);
    }
}
