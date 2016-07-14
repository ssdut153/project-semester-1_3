#include "expressionwindow.h"

ExpressionWindow::ExpressionWindow(ChatWindow *parent):
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
    this->setMinimumSize(210, 250);
    this->setMaximumSize(210, 250);
    this->cancelButton->setGeometry(30, 200, 150, 30);

    this->setWindowFlags(Qt::FramelessWindowHint);

    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, 210));
    linearGradient.setColorAt(0, QColor(133, 218, 223));
    linearGradient.setColorAt(1, QColor(255, 255, 255));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(linearGradient));
    this->setPalette(palette);

    this->dahanButton->setGeometry(30, 130, 50, 50);
    this->fennuButton->setGeometry(30, 80, 50, 50);
    this->guaiqiaoButton->setGeometry(30, 30, 50, 50);
    this->hechaButton->setGeometry(80, 130, 50, 50);
    this->kaixinButton->setGeometry(80, 80, 50, 50);
    this->penshuiButton->setGeometry(80, 30, 50, 50);
    this->weixiaoButton->setGeometry(130, 130, 50, 50);
    this->yinxianButton->setGeometry(130, 80, 50, 50);
    this->huajiButton->setGeometry(130, 30, 50, 50);


    this->huajiButton->setIcon(QIcon(":/expressions/huaji"));
    this->dahanButton->setIcon(QIcon(":/expressions/dahan"));
    this->fennuButton->setIcon(QIcon(":/expressions/fennu"));
    this->guaiqiaoButton->setIcon(QIcon(":/expressions/guaiqiao"));
    this->hechaButton->setIcon(QIcon(":/expressions/hecha"));
    this->kaixinButton->setIcon(QIcon(":/expressions/kaixin"));
    this->penshuiButton->setIcon(QIcon(":/expressions/penshui"));
    this->weixiaoButton->setIcon(QIcon(":/expressions/weixiao"));
    this->yinxianButton->setIcon(QIcon(":/expressions/yinxian"));

    this->huajiButton->setIconSize(QSize(50,50));
    this->dahanButton->setIconSize(QSize(50,50));
    this->fennuButton->setIconSize(QSize(50,50));
    this->guaiqiaoButton->setIconSize(QSize(50,50));
    this->hechaButton->setIconSize(QSize(50,50));
    this->kaixinButton->setIconSize(QSize(50,50));
    this->penshuiButton->setIconSize(QSize(50,50));
    this->weixiaoButton->setIconSize(QSize(50,50));
    this->yinxianButton->setIconSize(QSize(50,50));

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

void ExpressionWindow::addExpression(QString exp)
{
    chatwindow->getSendEdit()->setFocus();
    chatwindow->getSendEdit()->setText(chatwindow->getSendEdit()->toPlainText() + exp);
    QTextCursor cursor = chatwindow->getSendEdit()->textCursor();

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        chatwindow->getSendEdit()->setTextCursor(cursor);
    }

    chatwindow->setExpressionWindow(0);
    delete this;
}

void ExpressionWindow::on_huajiButton_clicked()
{
    this->addExpression("(#滑稽)");
}

void ExpressionWindow::on_dahanButton_clicked()
{
    this->addExpression("(#大汗)");

}

void ExpressionWindow::on_fennuButton_clicked()
{
    this->addExpression("(#愤怒)");
}

void ExpressionWindow::on_guaiqiaoButton_clicked()
{
    this->addExpression("(#乖巧)");
}

void ExpressionWindow::on_hechaButton_clicked()
{
    this->addExpression("(#喝茶)");
}

void ExpressionWindow::on_kaixinButton_clicked()
{
    this->addExpression("(#开心)");
}

void ExpressionWindow::on_penshuiButton_clicked()
{
    this->addExpression("(#喷水)");
}

void ExpressionWindow::on_weixiaoButton_clicked()
{
    this->addExpression("(#微笑)");
}

void ExpressionWindow::on_yinxianButton_clicked()
{
    this->addExpression("(#阴险)");
}

void ExpressionWindow::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void ExpressionWindow::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void ExpressionWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}
