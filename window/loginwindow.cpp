#include "loginwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/loginout/loginmessage.h"
#include "messagebox/exitmessagebox.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    loginGroupBox(new LoginGroupBox(this)),
    waitingGroupBox(new WaitingGroupBox(this)),
    closeButton(new CloseButton(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);



    this->setMaximumSize(400,280);
    this->setMinimumSize(400,280);
    QPalette palette;
    palette.setBrush(QPalette::Background, QPixmap(":/images/Login_a"));
    this->setPalette(palette);
    this->closeButton->setGeometry(365,1,35,35);

    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(on_closeButton_clicked()));

}

LoginGroupBox *LoginWindow::getLoginGroupBox()
{
    return this->loginGroupBox;
}

void LoginWindow::loginFail()
{
    CommonElements *ce = CommonElements::getInstance();
    ce->disconnectServer();
    this->loginGroupBox->getPasswordEdit()->clear();
    this->loginGroupBox->getMessageLabel()->setText("用户名或密码错误");
    this->loginGroupBox->show();
    this->waitingGroupBox->hide();
    this->loginGroupBox->getUsernameEdit()->setFocus();
}

WaitingGroupBox *LoginWindow::getWaitingGroupBox()
{
    return this->waitingGroupBox;
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Helper *helper = Helper::getInstance();
    helper->quit();
}

void LoginWindow::on_closeButton_clicked()
{
    ExitMessageBox emb(this);
    if (emb.exec() == QMessageBox::AcceptRole)
    {
        CommonElements *ce = CommonElements::getInstance();
        ce->getTrayIcon()->hide();
        ce->getApplication()->quit();
    }
}
