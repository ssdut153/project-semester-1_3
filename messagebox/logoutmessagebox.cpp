#include "logoutmessagebox.h"

LogoutMessageBox::LogoutMessageBox(QWidget *parent):
    QMessageBox(parent),
    pressed(false)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)) | Qt::Tool | Qt::X11BypassWindowManagerHint);
    this->setWindowTitle("提示");
    this->setText("您的帐号已在其他设备上登录");
    this->addButton("确定", QMessageBox::AcceptRole);
}

LogoutMessageBox::~LogoutMessageBox()
{

}

void LogoutMessageBox::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void LogoutMessageBox::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void LogoutMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

void LogoutMessageBox::paintEvent(QPaintEvent *event)
{
    QImage imp(":/images/exitBox");
    QPainter painter(this);
    painter.drawImage(0, 0, imp.scaled(this->size()));
    QMessageBox::paintEvent(event);
}
