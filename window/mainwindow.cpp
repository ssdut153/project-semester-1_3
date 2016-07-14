#include "mainwindow.h"
#include "commonelements.h"
#include "helper.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    usernameLabel(new QLabel(this)),
    friendListWidget(new QListWidget(this)),
    searchButton(new QPushButton(this)),
    headButton(new QPushButton(this)),
    closeButton(new CloseButton(this)),
    minButton(new MiniumButton(this)),
    headSculp(new QLabel(this)),
    searchDialog(new SearchDialog),
    umanager(0),
    dmanager(0)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMinimumSize(300, 700);
    this->setMaximumSize(300, 700);

    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, 700));
    linearGradient.setColorAt(0, QColor(133, 218, 223));
    linearGradient.setColorAt(1, QColor(255, 255, 255));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(linearGradient));
    this->setPalette(palette);

    QFont font;
    font.setPointSize(16);

    this->usernameLabel->setGeometry(88, 47, 140, 40);
    this->friendListWidget->setGeometry(20, 110, 260, 480);
    this->searchButton->setGeometry(20, 600, 60, 30);
    this->headButton->setGeometry(100, 600, 60, 30);
    this->closeButton->setGeometry(270, 1, 30, 30);
    this->minButton->setGeometry(240, 1, 30, 30);
    this->headSculp->setGeometry(30, 42, 48, 48);

    this->usernameLabel->setFont(font);
    font.setPointSize(10);
    this->friendListWidget->setFont(font);


    QImage head(":/images/photo");
    head.scaled(30, 30, Qt::KeepAspectRatio);
    this->headSculp->setScaledContents(true);
    this->headSculp->setPixmap(QPixmap::fromImage(head));

    CommonElements *ce = CommonElements::getInstance();
    this->usernameLabel->setText(ce->getUsername());
    this->searchButton->setText("搜索");
    this->headButton->setText("上传头像");

    Database::getInstance(ce->getUsername());

    Helper *helper = Helper::getInstance();
    getFriendListMessage gflm(ce->getUsername());
    helper->writeClient(gflm);

    connect(this->searchButton, SIGNAL(clicked()), this,SLOT(on_searchButton_clicked()));
    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(this->minButton, SIGNAL(clicked()),this , SLOT(on_minButton_clicked()));
    connect(this->headButton, SIGNAL(clicked()), this, SLOT(on_headButton_clicked()));
    connect(this->friendListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_friendListWidget_doubleClicked(QListWidgetItem*)));

}

MainWindow::~MainWindow()
{
    delete this->searchDialog;
    if(dmanager!=0)
    {
        delete dmanager;
    }
    if(umanager!=0)
    {
        delete umanager;
    }
    for(QMap<QListWidgetItem*, ChatWindow*>::iterator it = chatWindows.begin(); it != chatWindows.end(); it++)
    {
        delete it.value();
        delete it.key();
    }
}

void MainWindow::loadFriendList(QMap<QString, int> &users)
{
    friendlist.clear();
    for(QMap<QString, int>::iterator it = users.begin(); it != users.end(); it++)
    {
        friendlist.insert(it.key(), it.value());
    }
    Database *db = Database::getInstance("");
    db->createFriendTables(users);
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
    updateHeadSculp();
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
                ChatWindow *cw = new ChatWindow(item);
                this->chatWindows.insert(item, cw);
                cw->show();
                return cw;
            }
        }
    }
    return 0;
}

SearchDialog *MainWindow::getSearchDialog()
{
    return this->searchDialog;
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

    Database *db = Database::getInstance("");
    db->createFriendTable(friendName);

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

void MainWindow::on_searchButton_clicked()
{
    searchDialog->show();
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
        cw = new ChatWindow(item);
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
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

void MainWindow::on_headButton_clicked()
{
    picPath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp *.gif)");
    if (!picPath.isNull())
    {
        QImage *img=new QImage;
        if(!(img->load(picPath)))
        {
            delete img;
            return;
        }
        img->save(QDir::currentPath() + "/headImages/head_" + this->usernameLabel->text() + ".png");
        QFile image(picPath);
        image.open(QIODevice::ReadOnly);
        QByteArray by_img = image.readAll();
        image.close();
        umanager = new QNetworkAccessManager(this);
        connect(umanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onUploadFinished(QNetworkReply*)));
        QString url = "ftp://103.13.222.121/wwwroot/touxiang/head_" + this->usernameLabel->text() + ".png";
        QUrl u(url);
        u.setPort(90);
        u.setUserName("upload");
        u.setPassword("killcaomai");
        umanager->put(QNetworkRequest(u), by_img);
        delete img;
        this->headButton->setText("上传中");
        this->headButton->setDisabled(true);
    }
}

void MainWindow::updateHeadSculp()
{
    QDir temp;
    QString path=QDir::currentPath()+"/headImages";
    bool exist = temp.exists(path);
    if(exist)
    {
        QFile tempFile(path + "/head_" + this->usernameLabel->text() + ".png");
        if(!tempFile.exists())
        {
            downloadHeadSculp();
        }
    }
    else
    {
        bool ok = temp.mkdir(path);
        if(ok)
        {
            downloadHeadSculp();
        }
    }
    if(QFile(QDir::currentPath() + "/headImages/head_" + this->usernameLabel->text() + ".png").exists())
    {
        QImage imgScaled(QDir::currentPath() + "/headImages/head_" + this->usernameLabel->text() + ".png");
        imgScaled.scaled(48, 48, Qt::KeepAspectRatio);
        this->headSculp->setScaledContents(true);
        this->headSculp->setPixmap(QPixmap::fromImage(imgScaled));
    }
}

void MainWindow::downloadHeadSculp()
{
    dPath = QDir::currentPath() + "/headImages/head_" + this->usernameLabel->text() + ".png";
    dmanager = new QNetworkAccessManager(this);
    connect(dmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadFinished(QNetworkReply*)));
    QString url = "http://upload.ssdut153.cn/touxiang/head_" + this->usernameLabel->text() + ".png";
    QUrl u(url);
    dmanager->get(QNetworkRequest(u));
}

void MainWindow::onUploadFinished(QNetworkReply *)
{
    this->headButton->setText("上传头像");
    this->headButton->setDisabled(false);
    if(QFile(QDir::currentPath() + "/headImages/head_" + this->usernameLabel->text() + ".png").exists())
    {
        QImage imgScaled(QDir::currentPath() + "/headImages/head_" + this->usernameLabel->text() + ".png");
        imgScaled.scaled(48, 48, Qt::KeepAspectRatio);
        this->headSculp->setScaledContents(true);
        this->headSculp->setPixmap(QPixmap::fromImage(imgScaled));
    }
}

void MainWindow::onDownloadFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QImage *img=new QImage;
        img->loadFromData(reply->readAll());
        if(!(img->isNull()))
        {
            img->save(dPath);
            if(QFile(dPath).exists())
            {
                QImage imgScaled(dPath);
                imgScaled.scaled(48, 48, Qt::KeepAspectRatio);
                this->headSculp->setScaledContents(true);
                this->headSculp->setPixmap(QPixmap::fromImage(imgScaled));
            }
        }
        delete img;
    }
}

void MainWindow::on_minButton_clicked()
{
    this->hide();
}
