#include "loginwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "messagebox/exitmessagebox.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    loginGroupBox(new LoginGroupBox(this)),
    waitingGroupBox(new WaitingGroupBox(this)),
    closeButton(new CloseButton(this)),
    minButton(new MiniumButton(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMaximumSize(400, 280);
    this->setMinimumSize(400, 280);

    this->closeButton->setGeometry(370, 1, 30, 30);
    this->minButton->setGeometry(340,1,30,30);

    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, 400));
    linearGradient.setColorAt(0, QColor(133, 218, 223));
    linearGradient.setColorAt(1, QColor(255, 255, 255));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(linearGradient));
    this->setPalette(palette);

    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(this->minButton, SIGNAL(clicked()), this, SLOT(on_minButton_clicked()));

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

void LoginWindow::on_minButton_clicked()
{
    this->hide();
}
