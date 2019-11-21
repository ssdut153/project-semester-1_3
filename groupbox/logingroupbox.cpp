#include "logingroupbox.h"
#include "commonelements.h"
#include "helper.h"
#include "window/loginwindow.h"

LoginGroupBox::LoginGroupBox(QWidget *parent):
    QGroupBox(parent),
    messageLabel(new QLabel(this)),
    usernameEdit(new QLineEdit(this)),
    passwordEdit(new QLineEdit(this)),
    loginButton(new QPushButton(this)),
    regButton(new QPushButton(this)),
    headSculp(new QLabel(this)),
    aboutUs(new QLabel(this)),
    regDialog(nullptr),
    pressed(false)
{
    this->setGeometry(0, 0, 400, 280);

    QFont font;
    font.setPointSize(10);

    this->regButton->setFocusPolicy(Qt::ClickFocus);
    this->passwordEdit->setEchoMode(QLineEdit::Password);
    this->aboutUs->setOpenExternalLinks(true);
    this->usernameEdit->setFocus();

    this->usernameEdit->setPlaceholderText("请输入用户名");
    this->passwordEdit->setPlaceholderText("请输入密码");
    this->loginButton->setText("登  陆");
    this->regButton->setText("免费注册");
    this->aboutUs->setText("<style>a{text-decoration: none;}</style><a href=\"http://ssdut153.cn/\">  关于我们");

    QPalette pal = this->regButton->palette();
    pal.setColor(QPalette::ButtonText, QColor(28, 0, 255));

    this->regButton->setPalette(pal);
    this->loginButton->setFont(font);
    this->regButton->setFont(font);
    this->aboutUs->setFont(font);
    this->usernameEdit->setFont(font);
    this->passwordEdit->setFont(font);
    this->messageLabel->setFont(font);

    pal = this->messageLabel->palette();
    pal.setColor(QPalette::WindowText, Qt::red);
    this->messageLabel->setPalette(pal);

    this->messageLabel->setGeometry(109, 80, 192, 32);
    this->usernameEdit->setGeometry(107, 108, 192, 32);
    this->passwordEdit->setGeometry(107, 150, 192, 32);
    this->loginButton->setGeometry(106, 220, 194, 32);
    this->regButton->setGeometry(306, 108, 65, 32);
    this->headSculp->setGeometry(23, 108, 74, 74);
    this->aboutUs->setGeometry(313, 150, 65, 32);

    this->usernameEdit->setStyleSheet("border:2px;");

    this->passwordEdit->setStyleSheet("border:2px;");

    this->regButton->setStyleSheet("QPushButton{background-color:rgba(244,13,100,0);border:0px;}"
                                   "QPushButton:hover{color:white;}"
                                   "QPushButton:focus{border:0px;}");

    QImage head(":/images/photo");
    head.scaled(74, 74, Qt::KeepAspectRatio);
    this->headSculp->setScaledContents(true);
    this->headSculp->setPixmap(QPixmap::fromImage(head));

    this->setTabOrder(this->usernameEdit, this->passwordEdit);
    this->setTabOrder(this->passwordEdit, this->loginButton);
    this->setTabOrder(this->loginButton, this->usernameEdit);

    connect(this->loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    connect(this->regButton, SIGNAL(clicked()), this, SLOT(on_regButton_clicked()));
    connect(this->usernameEdit,SIGNAL(textChanged(QString)),this, SLOT(on_usernameEdit_textChanged()));

}

LoginGroupBox::~LoginGroupBox()
{
    if(this->regDialog != nullptr)
    {
        delete this->regDialog;
        this->regDialog = nullptr;
    }
}

void LoginGroupBox::on_loginButton_clicked()
{
    QString username = this->usernameEdit->text();
    QString password = this->passwordEdit->text();
    if(username == "")
    {
        this->messageLabel->setText("请输入用户名");
    }
    else if(password == "")
    {
        this->messageLabel->setText("请输入密码");
    }
    else
    {
        this->hide();
        CommonElements *ce = CommonElements::getInstance();
        ce->getLoginWindow()->getWaitingGroupBox()->show();
        ce->getLoginWindow()->getWaitingGroupBox()->getCancelButton()->setFocus();
        this->messageLabel->clear();
//        ce->connectServer();
        loginMessage lm(username, password);
        Helper::getInstance()->writeClient(lm);
    }
}

void LoginGroupBox::on_regButton_clicked()
{
    this->regDialog = new RegDialog;
    this->regDialog->show();
}

void LoginGroupBox::keyPressEvent(QKeyEvent *event)
{
    QWidget *widget = focusWidget();
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(!(this->isHidden() || pressed))
        {
            if(widget == this->usernameEdit || widget == this->passwordEdit || widget == this->loginButton)
            {
                this->on_loginButton_clicked();
            }
            else if(widget == this->regButton)
            {
                this->on_regButton_clicked();
            }
        }
        break;
    }
}

void LoginGroupBox::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void LoginGroupBox::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void LoginGroupBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        CommonElements *ce = CommonElements::getInstance();
        LoginWindow *lw = ce->getLoginWindow();
        lw->move(lw->x() + temp.x() - this->place.x(), lw->y() + temp.y() - this->place.y());
    }
}

QLabel *LoginGroupBox::getMessageLabel()
{
    return this->messageLabel;
}

QLineEdit *LoginGroupBox::getUsernameEdit()
{
    return this->usernameEdit;
}

QLineEdit *LoginGroupBox::getPasswordEdit()
{
    return this->passwordEdit;
}

RegDialog *LoginGroupBox::getRegDialog()
{
    return this->regDialog;
}

void LoginGroupBox::setRegDialog(RegDialog *regDialog)
{
    this->regDialog = regDialog;
}

void LoginGroupBox::on_usernameEdit_textChanged()
{
    QDir temp;
    QString path = QDir::currentPath() + "/headImages";
    if(!temp.exists(path))
    {
        return;
    }
    QDir dir(path);
    QStringList filter;
    filter << "*.png";
    dir.setNameFilters(filter);
    QList<QFileInfo> fileInfo(dir.entryInfoList(filter));
    for(int i = 0; i < fileInfo.count(); i++)
    {
        if(fileInfo.at(i).fileName() == "head_" + this->usernameEdit->text() + ".png")
        {
            QImage head(fileInfo.at(i).filePath());
            head.scaled(74, 74, Qt::KeepAspectRatio);
            this->headSculp->setScaledContents(true);
            this->headSculp->setPixmap(QPixmap::fromImage(head));
            return;
        }
    }

}
