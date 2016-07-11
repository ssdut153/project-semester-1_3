#include "searchwindow.h"
#include "commonelements.h"
#include "common/message/addfriend/addfriendmessage.h"
#include "common/message/searchuser/searchusermessage.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    searchEdit(new QLineEdit(this)),
    searchButton(new QPushButton(this)),
    resultLabel(new QLabel(this)),
    addButton(new QPushButton(this)),
    closeButton(new CloseButton(this))
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMaximumSize(400, 280);
    this->setMinimumSize(400, 280);

    QPalette palette;
    palette.setBrush(QPalette::Background, QPixmap(":/images/loginFinal_1"));
    this->setPalette(palette);

    this->searchButton->setText("查询");
    this->addButton->setText("添加");

    this->searchEdit->setGeometry(20, 50, 250, 30);
    this->searchButton->setGeometry(320, 50, 60, 30);
    this->resultLabel->setGeometry(20, 100, 150, 30);
    this->addButton->setGeometry(170, 100, 60, 30);
    this->closeButton->setGeometry(370,0,30,30);



    this->resultLabel->hide();
    this->addButton->hide();

    connect(this->searchButton, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));
    connect(this->addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(on_closeButton_clicked()));
}

void SearchWindow::on_searchButton_clicked()
{
    this->resultLabel->clear();
    this->resultLabel->hide();
    this->addButton->hide();
    QString searchName = this->searchEdit->text();
    if(searchName != "")
    {
        searchUserMessage sum(searchName);
        Helper *helper = Helper::getInstance();
        helper->writeClient(sum);
    }
}

void SearchWindow::on_addButton_clicked()
{
    QString addName = this->resultLabel->text();
    if(addName != "")
    {
        CommonElements *ce = CommonElements::getInstance();
        addFriendMessage afm(ce->getUsername(), addName);
        Helper *helper = Helper::getInstance();
        helper->writeClient(afm);
    }
}

void SearchWindow::showSearchUser(QString searchName)
{
    this->resultLabel->setText(searchName);
    this->resultLabel->show();
    this->addButton->show();
}

void SearchWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    this->searchEdit->clear();
    this->resultLabel->clear();
    this->resultLabel->hide();
    this->addButton->hide();
//    CommonElements::getInstance()->getMainWindow()->setSearchWindow(0);
//    this->deleteLater();
//    delete this;
}

void SearchWindow::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void SearchWindow::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void SearchWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

void SearchWindow::on_closeButton_clicked()
{
    this->hide();
    this->searchEdit->clear();
    this->resultLabel->clear();
    this->resultLabel->hide();
    this->addButton->hide();
}
