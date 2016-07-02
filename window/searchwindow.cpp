#include "searchwindow.h"
#include "commonelements.h"
#include "common/message/addfriend/addfriendmessage.h"
#include "common/message/searchuser/searchusermessage.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    searchEdit(new QLineEdit(this)),
    searchButton(new QPushButton(this)),
    resultLabel(new QLabel(this)),
    addButton(new QPushButton(this))
{
    this->setMaximumSize(400, 300);
    this->setMinimumSize(400, 300);

    this->searchButton->setText("查询");
    this->addButton->setText("添加");

    this->searchEdit->setGeometry(20, 30, 300, 30);
    this->searchButton->setGeometry(320, 30, 60, 30);
    this->resultLabel->setGeometry(20, 80, 150, 30);
    this->addButton->setGeometry(170, 80, 60, 30);

    this->resultLabel->hide();
    this->addButton->hide();

    connect(this->searchButton, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));
    connect(this->addButton, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));

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
