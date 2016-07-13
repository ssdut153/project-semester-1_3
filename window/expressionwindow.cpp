#include "expressionwindow.h"

ExpressionWindow::ExpressionWindow(ChatWindow *parent):
    QMainWindow(parent),
    huajiButton(new QPushButton(this)),
    dahanButton(new QPushButton(this)),
    fennuButton(new QPushButton(this)),
    guaiqiaoButton(new QPushButton(this)),
    hechaButton(new QPushButton(this)),
    kaixinButton(new QPushButton(this)),
    penshuiButton(new QPushButton(this)),
    weixiaoButton(new QPushButton(this)),
    yinxianButton(new QPushButton(this)),
    cancelButton(new QPushButton(this)),
    chatwindow(parent)
{
    this->setMinimumSize(300, 350);
    this->cancelButton->setGeometry(50, 310, 200, 30);

    this->dahanButton->setGeometry(25, 225, 50, 50);
    this->fennuButton->setGeometry(25, 125, 50, 50);
    this->guaiqiaoButton->setGeometry(25, 25, 50, 50);
    this->hechaButton->setGeometry(125, 225, 50, 50);
    this->kaixinButton->setGeometry(125, 125, 50, 50);
    this->penshuiButton->setGeometry(125, 25, 50, 50);
    this->weixiaoButton->setGeometry(225, 225, 50, 50);
    this->yinxianButton->setGeometry(225, 125, 50, 50);
    this->huajiButton->setGeometry(225, 25, 50, 50);

    this->huajiButton->setText("滑稽");
    this->dahanButton->setText("大汗");
    this->fennuButton->setText("愤怒");
    this->guaiqiaoButton->setText("乖巧");
    this->hechaButton->setText("喝茶");
    this->kaixinButton->setText("开心");
    this->penshuiButton->setText("喷水");
    this->weixiaoButton->setText("微笑");
    this->yinxianButton->setText("阴险");
    this->cancelButton->setText("取消");


    connect(huajiButton, SIGNAL(clicked()), this, SLOT(on_huajiButton_clicked()));
    connect(dahanButton, SIGNAL(clicked()), this, SLOT(on_dahanButton_clicked()));
    connect(fennuButton, SIGNAL(clicked()), this, SLOT(on_fennuButton_clicked()));
    connect(guaiqiaoButton, SIGNAL(clicked()), this, SLOT(on_guaiqiaoButton_clicked()));
    connect(hechaButton, SIGNAL(clicked()), this, SLOT(on_hechaButton_clicked()));
    connect(kaixinButton, SIGNAL(clicked()), this, SLOT(on_kaixinButton_clicked()));
    connect(penshuiButton, SIGNAL(clicked()), this, SLOT(on_penshuiButton_clicked()));
    connect(weixiaoButton, SIGNAL(clicked()), this, SLOT(on_weixiaoButton_clicked()));
    connect(yinxianButton, SIGNAL(clicked()), this, SLOT(on_yinxianButton_clicked()));

    connect(cancelButton, SIGNAL(clicked()), this,SLOT(on_cancelButton_clicked()));

}

void ExpressionWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    chatwindow->setExpressionWindow(0);
    delete this;
}



void ExpressionWindow::on_cancelButton_clicked()
{
    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_huajiButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#滑稽)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_dahanButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#大汗)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_fennuButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#愤怒)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_guaiqiaoButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#乖巧)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_hechaButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#喝茶)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_kaixinButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#开心)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_penshuiButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#喷水)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_weixiaoButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#微笑)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_yinxianButton_clicked(){
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + "(#阴险)");
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}
