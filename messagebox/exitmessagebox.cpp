#include "exitmessagebox.h"

ExitMessageBox::ExitMessageBox(QWidget *parent):
    QMessageBox(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    this->setWindowTitle("警告");
    this->setText("您真的要退出吗?");
    this->addButton("是", QMessageBox::AcceptRole);
    this->addButton("否", QMessageBox::RejectRole);
}

ExitMessageBox::~ExitMessageBox()
{

}
