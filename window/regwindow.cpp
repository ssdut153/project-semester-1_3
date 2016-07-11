#include "regwindow.h"
#include "commonelements.h"
#include "common/message/reg/regusermessage.h"

RegWindow::RegWindow(QWidget *parent) :
    QMainWindow(parent),
    messageLabel(new QLabel(this)),
    usernameEdit(new QLineEdit(this)),
    passwordEdit_1(new QLineEdit(this)),
    passwordEdit_2(new QLineEdit(this)),
    regButton(new QPushButton(this)),
    closeButton(new CloseButton(this))
{
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMaximumSize(280, 196);
    this->setMinimumSize(280, 196);
    QPalette palette;
    palette.setBrush(QPalette::Background, QPixmap(":/images/regWindow"));
    this->setPalette(palette);
    palette.setColor(QPalette::WindowText, Qt::red);
    this->messageLabel->setPalette(palette);

    this->usernameEdit->setFocus();

    this->usernameEdit->setPlaceholderText("请输入用户名(2-20位)");
    this->passwordEdit_1->setPlaceholderText("请输入密码(6-16位)");
    this->passwordEdit_2->setPlaceholderText("请确认密码");
    this->regButton->setText("注     册");

    this->usernameEdit->setStyleSheet("border:0px;");
    this->passwordEdit_1->setStyleSheet("border:0px;");
    this->passwordEdit_2->setStyleSheet("border:0px;");

    this->messageLabel->setGeometry(50, 10, 180, 20);
    this->usernameEdit->setGeometry(50, 30, 180, 30);
    this->passwordEdit_1->setGeometry(50, 70, 180, 30);
    this->passwordEdit_2->setGeometry(50, 110, 180, 30);
    this->regButton->setGeometry(50, 150, 180, 30);
    this->closeButton->setGeometry(250,1,30,30);

    this->setTabOrder(this->usernameEdit, this->passwordEdit_1);
    this->setTabOrder(this->passwordEdit_1, this->passwordEdit_2);
    this->setTabOrder(this->passwordEdit_2, this->regButton);
    this->setTabOrder(this->regButton, this->usernameEdit);

    connect(this->regButton, SIGNAL(clicked()), this, SLOT(on_regButton_clicked()));
    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));

}

void RegWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        this->on_regButton_clicked();
        break;
    case Qt::Key_Escape:
        CommonElements *ce = CommonElements::getInstance();
        ce->getLoginWindow()->getLoginGroupBox()->setRegWindow(0);
        delete this;
    }
}

void RegWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    CommonElements *ce = CommonElements::getInstance();
    ce->getLoginWindow()->getLoginGroupBox()->setRegWindow(0);
    delete this;
}

void RegWindow::on_closeButton_clicked()
{

    CommonElements *ce = CommonElements::getInstance();
    ce->getLoginWindow()->getLoginGroupBox()->setRegWindow(0);
    delete this;
}

void RegWindow::on_regButton_clicked()
{
    QString username = this->usernameEdit->text();
    QString password_1 = this->passwordEdit_1->text();
    QString password_2 = this->passwordEdit_2->text();
    if(username == "")
    {
        this->messageLabel->setText("请输入用户名");
    }
    else if(username.length() < 3 || username.length() > 20)
    {
        this->messageLabel->setText("用户名应在3-20位");
    }
    else if(password_1 == "")
    {
        this->messageLabel->setText("请输入密码");
    }
    else if(password_1.length() < 6 || password_1.length() > 16)
    {
        this->messageLabel->setText("密码应在6-16位");
    }
    else if(!(password_2 == password_1))
    {
        this->messageLabel->setText("两次输入密码不一致");
    }
    else
    {
        this->regButton->setEnabled(false);
        regUserMessage rum(username, password_1);
        CommonElements *ce = CommonElements::getInstance();
        this->username = username;
        this->password = password_1;
        ce->connectServer();
        Helper::getInstance()->writeClient(rum);
    }
}

void RegWindow::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void RegWindow::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void RegWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

QLabel *RegWindow::getMessageLabel()
{
    return this->messageLabel;
}

QPushButton *RegWindow::getRegButton()
{
    return this->regButton;
}

QString RegWindow::getUsername()
{
    return this->username;
}

QString RegWindow::getPassword()
{
    return this->password;
}
