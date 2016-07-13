#include "expressionwindow.h"

ExpressionWindow::ExpressionWindow(ChatWindow *parent):
    QMainWindow(parent),
    comfirmButton(new QPushButton(this)),
    cancelButton(new QPushButton(this)),
    expressions(new QComboBox(this)),
    chatwindow(parent)
{
    this->setMinimumSize(200, 200);
    this->expressions->setGeometry(50, 80, 100, 30);
    this->comfirmButton->setGeometry(20, 150, 60, 30);
    this->cancelButton->setGeometry(120, 150, 60, 30);

    this->comfirmButton->setText("选择");
    this->cancelButton->setText("取消");

    this->expressions->addItem("滑稽");
    this->expressions->addItem("阴险");
    this->expressions->addItem("大汗");
    this->expressions->addItem("愤怒");
    this->expressions->addItem("乖巧");
    this->expressions->addItem("喝茶");
    this->expressions->addItem("开心");
    this->expressions->addItem("喷水");
    this->expressions->addItem("微笑");

    connect(comfirmButton, SIGNAL(clicked()), this, SLOT(on_comfirmButton_clicked()));
    connect(cancelButton, SIGNAL(clicked()), this,SLOT(on_cancelButton_clicked()));

}

void ExpressionWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_comfirmButton_clicked()
{
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#" + expressions->currentText() + ")");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;

}

void ExpressionWindow::on_cancelButton_clicked()
{
    chatwindow->setExpressionWindow(0);
    delete this;
}
