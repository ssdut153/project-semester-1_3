#include "mainwindow.h"
#include "commonelements.h"
#include "helper.h"
#include "common/message/friendlist/getfriendlistmessage.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    usernameLabel(new QLabel(this)),
    friendListWidget(new QListWidget(this)),
    searchButton(new QPushButton(this)),
    headButton(new QPushButton(this)),
    closeButton(new CloseButton(this)),
    headSculp(new QLabel(this)),
    searchWindow(new SearchWindow(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);


    this->setMinimumSize(300, 700);
    this->setMaximumSize(300, 700);

    QPalette palette;
    palette.setBrush(QPalette::Background, QPixmap(":/images/mainWindow_1"));
    this->setPalette(palette);

    this->usernameLabel->setGeometry(70, 60, 140, 30);
    this->friendListWidget->setGeometry(20, 110, 260, 480);
    this->searchButton->setGeometry(20, 600, 60, 30);
    this->headButton->setGeometry(100,600,60,30);
    this->closeButton->setGeometry(270,1,30,30);
    this->headSculp->setGeometry(30, 60, 30, 30);

    QImage head(":/images/photo");
    head.scaled(30, 30, Qt::KeepAspectRatio);
    this->headSculp->setScaledContents(true);
    this->headSculp->setPixmap(QPixmap::fromImage(head));

    CommonElements *ce = CommonElements::getInstance();
    usernameLabel->setText(ce->getUsername());
    this->searchButton->setText("搜索");
    this->headButton->setText("上传头像");

    Database::getInstance(ce->getUsername());

    Helper *helper = Helper::getInstance();
    getFriendListMessage gflm(ce->getUsername());
    helper->writeClient(gflm);

    connect(this->searchButton, SIGNAL(clicked()), this,SLOT(on_searchButton_clicked()));
    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(this->headButton, SIGNAL(clicked()), this, SLOT(on_headButton_clicked()));
    connect(this->friendListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_friendListWidget_doubleClicked(QListWidgetItem*)));

}

void MainWindow::loadFriendList(QMap<QString, int> &users)
{
    friendlist.clear();
    for(QMap<QString, int>::iterator it = users.begin(); it != users.end(); it++)
    {
        friendlist.insert(it.key(), it.value());
    }
    Database *db = Database::getInstance("");
    if(db->createFriendTables(friendlist))
    {
        qDebug()<<"test";
    }
    for(QMap<QString, int>::iterator it = friendlist.begin();it != friendlist.end(); it++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        if(it.value() == 0)
        {
            item->setText(it.key() + "(离线)");
        }
        else if(it.value() == 1)
        {
            item->setText(it.key() + "(在线)");
        }
        this->items.push_back(item);
        this->friendListWidget->addItem(item);
    }
}

void MainWindow::setFriendStatus(QString friendName, bool online)
{
    int size = items.size();
    for(int i = 0;i < size;i++)
    {
        QListWidgetItem *item = items[i];
        if(item->text().left(item->text().size() - 4) == friendName)
        {
            if(online)
            {
                item->setText(friendName + "(在线)");
            }
            else
            {
                item->setText(friendName + "(离线)");
            }
        }
    }
}

QMap<QListWidgetItem*, ChatWindow*> &MainWindow::getChatWindows()
{
    return this->chatWindows;
}

ChatWindow *MainWindow::getChatWindow(QString friendName)
{
    int size = this->items.size();
    for(int i = 0;i <size;i++)
    {
        QListWidgetItem *item = this->items[i];
        QString name = item->text();
        if(name.left(name.size() - 4) == friendName)
        {
            if(this->chatWindows.contains(item))
            {
                return chatWindows.find(item).value();
            }
            else
            {
                ChatWindow *cw = new ChatWindow(item, this);
                this->chatWindows.insert(item, cw);
                cw->show();
                return cw;
            }
        }
    }
    return 0;
}

SearchWindow *MainWindow::getSearchWindow()
{
    return this->searchWindow;
}
void MainWindow::addFriendItem(QString friendName, int status)
{
    for(QMap<QString, int>::iterator it = friendlist.begin();it != friendlist.end(); it++)
    {
        if(it.key() == friendName)
        {
            return;
        }
    }
    QListWidgetItem *item = new QListWidgetItem;
    if(status == 0)
    {
        item->setText(friendName + "(离线)");
    }
    else if(status == 1)
    {
        item->setText(friendName + "(在线)");
    }
    this->items.push_back(item);
    this->friendListWidget->addItem(item);
}

//void MainWindow::setSearchWindow(SearchWindow *searchWindow)
//{
//    this->searchWindow = searchWindow;
//}

void MainWindow::on_searchButton_clicked()
{
    searchWindow->show();
}

void MainWindow::on_friendListWidget_doubleClicked(QListWidgetItem *item)
{
    ChatWindow *cw = 0;
    if(chatWindows.contains(item))
    {
        cw = chatWindows.find(item).value();
        cw->setFocus();
    }
    else
    {
        cw = new ChatWindow(item, this);
        this->chatWindows.insert(item, cw);
        cw->show();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Helper *helper = Helper::getInstance();
    helper->quit();
}

void MainWindow::on_closeButton_clicked()
{
    Helper *helper = Helper::getInstance();
    helper->quit();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        CommonElements *ce = CommonElements::getInstance();
        MainWindow *lw = ce->getMainWindow();
        lw->move(lw->x() + temp.x() - this->place.x(), lw->y() + temp.y() - this->place.y());
    }
}

void MainWindow::on_headButton_clicked()
{

}
