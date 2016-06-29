#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/searchuser/searchusermessage.h"
#include "common/message/addfriend/addfriendmessage.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
//    ui->searchGroupBox->hide();
}

void SearchWindow::showSearchUser(QString searchName)
{
    ui->userLabel->setText(searchName);
    ui->searchGroupBox->show();
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::on_searchButton_clicked()
{
    if(ui->searchEdit->text() != "")
    {
        QString username = ui->searchEdit->text();
        searchUserMessage sum(username);
        Helper *helper = Helper::getInstance();
        helper->writeClient(sum);
    }
}

void SearchWindow::closeEvent(QCloseEvent */*event*/)
{
    CommonElements *ce = CommonElements::getInstance();
    ce->mainWindow->searchWindow = 0;
    delete this;
}

void SearchWindow::on_addButton_clicked()
{
    CommonElements *ce = CommonElements::getInstance();
    addFriendMessage afm(ce->username, ui->searchEdit->text());
    Helper *helper = Helper::getInstance();
    helper->writeClient(afm);
}
