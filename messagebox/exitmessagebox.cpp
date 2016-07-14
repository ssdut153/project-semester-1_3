#include "exitmessagebox.h"

ExitMessageBox::ExitMessageBox(QWidget *parent):
    QMessageBox(parent),
    pressed(false)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)) | Qt::Tool | Qt::X11BypassWindowManagerHint);
    this->setWindowTitle("警告");
    this->setText("您真的要退出吗?");
    this->addButton("是", QMessageBox::AcceptRole);
    this->addButton("否", QMessageBox::RejectRole);
}

ExitMessageBox::~ExitMessageBox()
{

}

void ExitMessageBox::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void ExitMessageBox::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void ExitMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

void ExitMessageBox::paintEvent(QPaintEvent *event)
{
    QImage imp(":/images/exitBox");
    QPainter painter(this);
    painter.drawImage(0, 0, imp.scaled(this->size()));
    QMessageBox::paintEvent(event);
}
