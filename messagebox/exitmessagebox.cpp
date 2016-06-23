#include "exitmessagebox.h"

ExitMessageBox::ExitMessageBox(QObject *):
    QMessageBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint| (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    this->addButton("是", QMessageBox::AcceptRole);
    this->addButton("否", QMessageBox::RejectRole);
}

ExitMessageBox::~ExitMessageBox()
{

}
