#include "chatwindow.h"
#include "commonelements.h"
#include "helper.h"
#include "database.h"

ChatWindow::ChatWindow(QListWidgetItem *item, MainWindow *parent):
    QMainWindow(parent),
    username(CommonElements::getInstance()->getUsername()),
    item(item),
    friendName(item->text().left(item->text().size() - 4)),
    friendHead(new QLabel(this)),
    friendnameLabel(new QLabel(this)),
    messageEdit(new QTextEdit(this)),
    sendEdit(new QTextEdit(this)),
    sendButton(new QPushButton(this)),
    picButton(new QPushButton(this)),
    expressButton(new QPushButton(this)),
    filButton(new QPushButton(this)),
    closeButton(new CloseButton(this)),
    minButton(new MiniumButton(this)),
    trueImage(new QCheckBox(this)),
    manager(0),
    recmanager(0),
    filemanager(0),
    dmanager(0),
    pressed(false),
    expDialog(0)
{

    this->setWindowFlags(Qt::FramelessWindowHint/* | Qt::Tool*/ | Qt::X11BypassWindowManagerHint);

    this->setMinimumSize(800, 600);
    this->setMaximumSize(800, 600);

    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, 600));
    linearGradient.setColorAt(0, QColor(133, 218, 223));
    linearGradient.setColorAt(1, QColor(255, 255, 255));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(linearGradient));
    this->setPalette(palette);

    QFont font;
    font.setPointSize(16);

    this->setWindowTitle(this->friendName);

    this->sendButton->setText("发送");
    this->trueImage->setText("显示原图");

    this->trueImage->setChecked(false);

    this->messageEdit->setReadOnly(true);

    this->friendHead->setGeometry(60, 32, 48, 48);
    this->friendnameLabel->setGeometry(120,32, 200, 48);
    this->messageEdit->setGeometry(50, 85, 700, 285);
    this->sendEdit->setGeometry(50, 420, 700, 120);
    this->sendButton->setGeometry(710, 550, 60, 30);
    this->picButton->setGeometry(90, 380, 30, 30);
    this->expressButton->setGeometry(50, 380, 30, 30);
    this->filButton->setGeometry(130, 380, 30, 30);
    this->closeButton->setGeometry(770, 0, 30, 30);
    this->minButton->setGeometry(740, 0, 30, 30);
    this->trueImage->setGeometry(170, 380, 80, 30);

    QImage head(":/images/photo");
    head.scaled(48, 48, Qt::KeepAspectRatio);
    this->friendHead->setScaledContents(true);
    this->friendHead->setPixmap(QPixmap::fromImage(head));
    this->friendnameLabel->setText(this->friendName);
    this->friendnameLabel->setFont(font);

    font.setPointSize(10);
    this->messageEdit->setFont(font);

    this->expressButton->setStyleSheet("QPushButton{border-image:url(:/images/expression);}"
                                       "QPushButton:hover{border-image:url(:/images/expression_1);}"
                                       "QPushButton:pressed{border-image:url(:/images/expression_2);}");
    this->picButton->setStyleSheet("QPushButton{border-image:url(:/images/pic_0);}"
                                   "QPushButton:hover{border-image:url(:/images/pic_1);}"
                                   "QPushButton:pressed{border-image:url(:/images/pic_2);}");
    this->filButton->setStyleSheet("QPushButton{border-image:url(:/images/file);}"
                                   "QPushButton:hover{border-image:url(:/images/file_1);}"
                                   "QPushButton:pressed{border-image:url(:/images/file_2);}");

    connect(this->sendButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked()));
    connect(this->picButton, SIGNAL(clicked()), this, SLOT(on_picButton_clicked()));
    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(this->minButton, SIGNAL(clicked()), this, SLOT(on_minButton_clicked()));
    connect(this->expressButton, SIGNAL(clicked()), this, SLOT(on_expressButton_clicked()));
    connect(this->filButton, SIGNAL(clicked()), this, SLOT(on_filButton_clicked()));

    expMap.insert("huaji", "(#滑稽)");
    expMap.insert("dahan", "(#大汗)");
    expMap.insert("fennu", "(#愤怒)");
    expMap.insert("guaiqiao", "(#乖巧)");
    expMap.insert("hecha", "(#喝茶)");
    expMap.insert("kaixin", "(#开心)");
    expMap.insert("penshui", "(#喷水)");
    expMap.insert("weixiao", "(#微笑)");
    expMap.insert("yinxian", "(#阴险)");

    dPath = QDir::currentPath() + "/headImages/head_" + this->friendName + ".png";
    updateFriendHead();

    Database *db = Database::getInstance("");

    db->loadMessage(this, this->friendName);

}

QTextEdit *ChatWindow::getMessageEdit()
{
    return this->messageEdit;
}

void ChatWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    CommonElements *ce = CommonElements::getInstance();
    ce->getMainWindow()->getChatWindows().remove(this->item);
    delete this;
}

void ChatWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        this->on_sendButton_clicked();
        break;
    }
}

void ChatWindow::on_sendButton_clicked()
{
    QString content = this->sendEdit->toPlainText();
    if(content != "")
    {
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        p2pMessage pm(this->username, this->friendName, time, content);
        Helper *helper = Helper::getInstance();
        helper->writeClient(pm);
        this->sendEdit->clear();
        this->messageEdit->append(QString("<span style=\"color: blue;\">") + this->username +  "</span> <span style=\"color:cyan;\">" + time + "</span>");
        readContent(content);
        Database *db = Database::getInstance(this->username);
        db->addMessage(this->friendName, 1, time, content);
    }
}

void ChatWindow::on_picButton_clicked()
{
    picPath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp *.gif)");
    if (!picPath.isNull())
    {
        QImage *img = new QImage;
        if(!(img->load(picPath)))
        {
            delete img;
            return;
        }
        QFile image(picPath);
        image.open(QIODevice::ReadOnly);

        QByteArray by_img = image.readAll();
        image.close();
        manager = new QNetworkAccessManager(this);
        imgTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
        QString url = "ftp://103.13.222.121/wwwroot/chatpic/" + this->username + "_" + this->friendName + "_" + imgTime + ".png";

        QUrl u(url);
        u.setPort(90);
        u.setUserName("upload");
        u.setPassword("killcaomai");
        manager->put(QNetworkRequest(u), by_img);
        this->sendButton->setDisabled(true);
        this->picButton->setDisabled(true);
        this->filButton->setDisabled(true);
        delete img;
    }
}

void ChatWindow::receivePic(imageMessage im)
{
    recmanager = new QNetworkAccessManager(this);
    connect(recmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReceiveFinished(QNetworkReply*)));
    QString url = QString("http://upload.ssdut153.cn/chatpic/") + im.FromUserName + "_" + im.ToUserName + "_" + im.CreateTime + ".png";

    QUrl u(url);
    recmanager->get(QNetworkRequest(u));
    this->sendButton->setDisabled(true);
    this->picButton->setDisabled(true);
    this->filButton->setDisabled(true);

}

void ChatWindow::onFinished(QNetworkReply *reply)
{

    if(reply->error() == QNetworkReply::NoError)
    {
        imageMessage im(this->username, this->friendName, imgTime);
        Helper *helper = Helper::getInstance();
        helper->writeClient(im);

        messageEdit->append(this->username + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        this->messageEdit->append("");

        QUrl uri(QString("file://%1").arg(picPath));
        QImage image = QImageReader(picPath).read();
        QTextDocument * textDocument = this->messageEdit->document();
        textDocument->addResource( QTextDocument::ImageResource, uri, QVariant(image));
        QTextCursor cursor = this->messageEdit->textCursor();
        QTextImageFormat imageFormat;

        if(trueImage->isChecked())
        {
            imageFormat.setWidth(image.width());
            imageFormat.setHeight(image.height());
        }
        else
        {
            if(image.height() > 200)
            {
                imageFormat.setWidth((double) image.width() / image.height() * 200);
                imageFormat.setHeight(200);
            }
            else
            {
                imageFormat.setWidth(image.width());
                imageFormat.setHeight(image.height());
            }
        }
        imageFormat.setName(uri.toString());
        cursor.insertImage(imageFormat);
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
    }
    else
    {
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
        this->messageEdit->append("发送失败");
    }
}

void ChatWindow::onReceiveFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QImage *img = new QImage;
        img->loadFromData(reply->readAll());

        img->save("./temp.png");
        messageEdit->append(this->friendName + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        messageEdit->append("");
        QString picPath = QDir::currentPath() + "/temp.png";

        QUrl uri(QString("file://%1").arg(picPath));
        QImage image = QImageReader(picPath).read();

        QTextDocument *textDocument = messageEdit->document();
        textDocument->addResource( QTextDocument::ImageResource, uri, QVariant(image));
        QTextCursor cursor = messageEdit->textCursor();
        QTextImageFormat imageFormat;

        if(trueImage->isChecked())
        {
            imageFormat.setWidth(image.width());
            imageFormat.setHeight(image.height());
        }
        else
        {
            if(image.height() > 200)
            {

                imageFormat.setWidth((double) image.width() / image.height() * 200);
                imageFormat.setHeight(200);
            }
            else
            {
                imageFormat.setWidth(image.width());
                imageFormat.setHeight(image.height());
            }
        }
        imageFormat.setName(uri.toString());
        cursor.insertImage(imageFormat);
        QFile::remove(picPath);
        delete img;
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
    }
    else
    {
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
        this->messageEdit->append("发送失败");
    }
}

void ChatWindow::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void ChatWindow::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void ChatWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

ChatWindow::~ChatWindow()
{
    if(manager != 0)
    {
        delete manager;
    }
    if(recmanager != 0)
    {
        delete recmanager;
    }
    if(filemanager!=0)
    {
        delete filemanager;
    }
}

void ChatWindow::on_closeButton_clicked()
{
    this->hide();
    CommonElements *ce = CommonElements::getInstance();
    ce->getMainWindow()->getChatWindows().remove(this->item);
    delete this;
}

void ChatWindow::on_expressButton_clicked()
{
    if(this->expDialog == 0)
    {
        this->expDialog = new ExpressionDialog(this);
        expDialog->show();
    }
}

void ChatWindow::setExpressionDialog(ExpressionDialog *exp)
{
    this->expDialog = exp;
}

QTextEdit* ChatWindow::getSendEdit()
{
    return this->sendEdit;
}

void ChatWindow::readContent(QString content)
{
    messageEdit->append("");

    int expst, forexpst = -5;
    QString exp;
    bool isExp = 0;

    QTextCursor cursor = messageEdit->textCursor();
    expst = content.indexOf("(", 0);

    do
    {
        if(expst == -1)
        {
            messageEdit->insertPlainText(content);
            if(!cursor.atEnd())
            {
                cursor.movePosition(QTextCursor::End);
                messageEdit->setTextCursor(cursor);
            }
            return;
        }
        else
        {
            exp = content.mid(expst, 5);
            for(QMap<QString, QString>::iterator it = expMap.begin();it != expMap.end(); it++)
            {
                if(exp == it.value())
                {
                    messageEdit->insertPlainText(content.mid(forexpst + 5, expst - forexpst - 5));
                    if(!cursor.atEnd())
                    {
                        cursor.movePosition(QTextCursor::End);
                        messageEdit->setTextCursor(cursor);
                    }
                    insertExp(it.key(), cursor);
                    isExp = true;
                }
            }
            if(!isExp)
            {
                expst = content.indexOf("(", expst + 1);
                continue;
            }
        }

        forexpst = expst;
        expst = content.indexOf("(", expst + 5);

    } while(expst != -1);

    messageEdit->insertPlainText(content.mid(forexpst + 5));

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        messageEdit->setTextCursor(cursor);
    }
}

void ChatWindow::insertExp(QString expKey, QTextCursor cursor)
{
    cursor.movePosition(QTextCursor::End);
    messageEdit->setTextCursor(cursor);
    cursor.insertImage(QImage(":/expressions/" + expKey));

    if(!cursor.atEnd())
    {
        cursor.movePosition(QTextCursor::End);
        messageEdit->setTextCursor(cursor);
    }
}

void ChatWindow::on_filButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this,"Open file", "", "All files(*.*)");
    if (!filePath.isNull())
    {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        fileFormalName = QFileInfo(filePath).fileName();
        filename = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss") + "." + QFileInfo(filePath).suffix();

        if(file.size()>2097152)
        {
            messageEdit->append("文件过大！发送的文件应不超过2mb。");
            return;
        }
        QByteArray by_file = file.readAll();
        file.close();

        filemanager = new QNetworkAccessManager(this);
        connect(filemanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFileFinished(QNetworkReply*)));
        QString url = "ftp://103.13.222.121/wwwroot/file/" + this->username + "_" + this->friendName + "_" + filename;

        QUrl u(url);
        u.setPort(90);
        u.setUserName("upload");
        u.setPassword("killcaomai");
        filemanager->put(QNetworkRequest(u), by_file);
        this->sendButton->setDisabled(true);
        this->sendButton->setText("发送中");
        this->picButton->setDisabled(true);
        this->filButton->setDisabled(true);
    }
}

void ChatWindow::onFileFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        fileMessage fm(this->username, this->friendName, filename, fileFormalName);
        Helper *helper = Helper::getInstance();
        helper->writeClient(fm);

        messageEdit->append(this->username + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        this->messageEdit->append("已向对方发送"+fileFormalName);

        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
        this->sendButton->setText("发送");
    }
    else
    {
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
        this->sendButton->setText("发送");
        this->messageEdit->append("发送失败");
    }
}


void ChatWindow::receiveFile(fileMessage fm)
{
    receiveFilename = fm.Content;
    fileRecManager = new QNetworkAccessManager(this);
    connect(fileRecManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFileReceiveFinished(QNetworkReply*)));
    QUrl u;
    u.setScheme("ftp");
    u.setHost("103.13.222.121");
    u.setPath("wwwroot/file/" + fm.FromUserName + "_" + fm.ToUserName + "_" + fm.CreateTime);
    u.setPort(90);
    u.setUserName("upload");
    u.setPassword("killcaomai");
    fileRecManager->get(QNetworkRequest(u));
    this->sendButton->setDisabled(true);
    this->sendButton->setText("接收文件中");
    this->picButton->setDisabled(true);
    this->filButton->setDisabled(true);
}

void ChatWindow::onFileReceiveFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QDir temp;
        QString path = QDir::currentPath() + "/fileReceive";
        bool exist = temp.exists(path);
        if(!exist)
        {
            bool ok = temp.mkdir(path);
            if(!ok)
            {
                return;
            }
        }
        QFile file(path + "/" + receiveFilename);
        file.open(QIODevice::WriteOnly);
        file.write(reply->readAll());
        file.flush();
        file.close();

        messageEdit->append(this->friendName + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        messageEdit->append("收到" + this->friendName + "发送的文件" + receiveFilename);
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
        this->sendButton->setText("发送");
    }
    else
    {
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->filButton->setDisabled(false);
        this->sendButton->setText("发送");
        this->messageEdit->append("发送失败");
    }

}

void ChatWindow::on_minButton_clicked()
{
    this->showMinimized();
}

void ChatWindow::updateFriendHead(){
    QDir temp;
    QString path=QDir::currentPath()+"/headImages";
    bool exist = temp.exists(path);
    if(!exist)
    {
        bool ok = temp.mkdir(path);
        if(!ok)
        {
            return;
        }
    }
    if(QFile(dPath).exists())
    {
        QImage imgScaled(dPath);
        imgScaled.scaled(48, 48, Qt::KeepAspectRatio);
        this->friendHead->setScaledContents(true);
        this->friendHead->setPixmap(QPixmap::fromImage(imgScaled));
    }

    dmanager = new QNetworkAccessManager(this);
    connect(dmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadFinished(QNetworkReply*)));
    QString url = "http://upload.ssdut153.cn/touxiang/head_" + this->friendName + ".png";
    QUrl u(url);
    dmanager->get(QNetworkRequest(u));
}

void ChatWindow::onDownloadFinished(QNetworkReply *reply)
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
                this->friendHead->setScaledContents(true);
                this->friendHead->setPixmap(QPixmap::fromImage(imgScaled));
            }
        }
        delete img;
    }
}
