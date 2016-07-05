#include "waitinggroupbox.h"

WaitingGroupBox::WaitingGroupBox(QWidget *parent):
    QGroupBox(parent),
    waitingLabel(new QLabel(this)),
    cancelButton(new QPushButton(this))
{
    this->waitingLabel->setText("正在登录");
    this->cancelButton->setText("取消");

    this->waitingLabel->setGeometry(100, 40, 60, 30);
    this->cancelButton->setGeometry(110, 90, 50, 30);

    this->setGeometry(0, 0, 270, 150);

    this->hide();

    this->setTabOrder(this->cancelButton, this->cancelButton);

    connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));
}

QPushButton *WaitingGroupBox::getCancelButton()
{
    return this->cancelButton;
}

void WaitingGroupBox::on_cancelButton_clicked()
{
    CommonElements *ce = CommonElements::getInstance();
    ce->disconnectServer();
    this->hide();
    ce->getLoginWindow()->getLoginGroupBox()->show();
    ce->getLoginWindow()->getLoginGroupBox()->getUsernameEdit()->setFocus();
}

void WaitingGroupBox::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(!(this->isHidden()))
        {
            this->on_cancelButton_clicked();
        }
        break;
    }
}

void WaitingGroupBox::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void WaitingGroupBox::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void WaitingGroupBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        CommonElements *ce = CommonElements::getInstance();
        LoginWindow *lw = ce->getLoginWindow();
        lw->move(lw->x() + temp.x() - this->place.x(), lw->y() + temp.y() - this->place.y());
    }
}
