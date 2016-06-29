#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "common/message/searchuser/searchusermessage.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
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
    }
}

void SearchWindow::closeEvent(QCloseEvent *event)
{
    delete this;
}
