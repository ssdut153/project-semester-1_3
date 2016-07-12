#include "addfriendmessagebox.h"

AddFriendMessageBox::AddFriendMessageBox(QString friendName, QWidget *parent):
    QMessageBox(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)) | Qt::Tool | Qt::X11BypassWindowManagerHint);
    this->setWindowTitle("好友添加请求");
    this->setText(friendName + "请求添加您为好友");
    this->addButton("同意", QMessageBox::AcceptRole);
    this->addButton("拒绝", QMessageBox::RejectRole);
}

AddFriendMessageBox::~AddFriendMessageBox()
{

}

void AddFriendMessageBox::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void AddFriendMessageBox::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void AddFriendMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

void AddFriendMessageBox::paintEvent(QPaintEvent *event)
{
    QImage imp(":/images/exitBox");
    QPainter painter(this);
    painter.drawImage(0, 0, imp.scaled(this->size()));
    QMessageBox::paintEvent(event);
}
