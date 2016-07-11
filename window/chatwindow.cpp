#include "chatwindow.h"
#include "commonelements.h"
#include "helper.h"
#include "common/message/function/p2pmessage.h"
#include "database.h"

ChatWindow::ChatWindow(QListWidgetItem *item, MainWindow *parent) :
    QMainWindow(parent),
    username(CommonElements::getInstance()->getUsername()),
    item(item),
    friendName(item->text().left(item->text().size() - 4)),
    messageEdit(new QTextEdit(this)),
    sendEdit(new QTextEdit(this)),
    sendButton(new QPushButton(this)),
    picButton(new QPushButton(this)),
    trueImage(new QRadioButton(this)),
    manager(0),
    recmanager(0)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMinimumSize(800, 600);
    this->setMaximumSize(800, 600);

    this->setWindowTitle(this->friendName);

    this->sendButton->setText("发送");
    this->picButton->setText("图");
    this->trueImage->setText("显示原图");

    this->trueImage->setChecked(false);

    this->messageEdit->setReadOnly(true);

    this->messageEdit->setGeometry(25, 20, 750, 380);
    this->sendEdit->setGeometry(25, 420, 750, 120);
    this->sendButton->setGeometry(710, 550, 60, 30);
    this->picButton->setGeometry(580, 550, 60, 30);
    this->trueImage->setGeometry(350, 550, 60, 30);

    connect(this->sendButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked()));
    connect(this->picButton, SIGNAL(clicked()), this, SLOT(on_picButton_clicked()));
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
    switch (event->key()) {
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
        p2pMessage pm(this->username, this->friendName,time, content);
        Helper *helper = Helper::getInstance();
        helper->writeClient(pm);
        this->sendEdit->clear();
        this->messageEdit->append(this->username + " " + time);
        this->messageEdit->append(content);
        Database *db = Database::getInstance(this->username);
        db->addMessage(this->friendName, 1, time, content);
    }
}
void ChatWindow::on_picButton_clicked(){
    picPath = QFileDialog::getOpenFileName(this,tr("Open Config"), "", tr("Image Files (*.png *.jpg *.bmp *.gif)"));
    if (!picPath.isNull())
    {
        QImage *img=new QImage;
        if(!(img->load(picPath)))
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
        QFile Image(picPath);
        Image.open(QIODevice::ReadOnly);
        qDebug()<<Image.isOpen();
        qDebug()<<picPath;
        QByteArray by_img=Image.readAll();
        Image.close();
        manager=new QNetworkAccessManager(this);
        imgTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinished(QNetworkReply*)));
        QString url="ftp://103.13.222.121/wwwroot/chatpic/"+this->username+"_"+this->friendName+"_"+imgTime+".png";
        qDebug()<<url;
        QUrl u(url);
        u.setPort(90);
        u.setUserName("upload");
        u.setPassword("killcaomai");
        manager->put(QNetworkRequest(u), by_img);
    }
    else{}
}
void ChatWindow::receivePic(imageMessage im){
    recmanager = new QNetworkAccessManager(this);
    connect(recmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReceiveFinished(QNetworkReply*)));
    QString url="http://upload.ssdut153.cn/chatpic/"+im.FromUserName+"_"+im.ToUserName+"_"+im.CreateTime+".png";
    qDebug()<<url;
    QUrl u(url);
    recmanager->get(QNetworkRequest(u));
}

void ChatWindow::onFinished(QNetworkReply *){

    imageMessage im(this->username, this->friendName,imgTime);
    Helper *helper = Helper::getInstance();
    helper->writeClient(im);

    qDebug("upload success");

    messageEdit->append(this->username +" "+ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    this->messageEdit->append("");
    QUrl Uri (QString("file://%1").arg (picPath));
    QImage image = QImageReader(picPath).read();
    QTextDocument * textDocument = this->messageEdit->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant(image));
    QTextCursor cursor = this->messageEdit->textCursor();
    QTextImageFormat imageFormat;
    if(trueImage->isChecked()){
        imageFormat.setWidth(image.width());
        imageFormat.setHeight(image.height());
    }
    else{
        if(image.height()>200){

            imageFormat.setWidth((double)image.width()/image.height()*200);
            imageFormat.setHeight(200);
        }
        else{
            imageFormat.setWidth(image.width());
            imageFormat.setHeight(image.height());
        }
    }
    imageFormat.setName(Uri.toString());
    cursor.insertImage(imageFormat);

}
void ChatWindow::onReceiveFinished(QNetworkReply *reply){
    if(reply->error()== QNetworkReply::NoError)

    {
        QImage *img=new QImage;
        img->loadFromData(reply->readAll());
        qDebug()<<img->isNull();
        img->save("./temp.png");
        messageEdit->append(this->friendName +" "+ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        messageEdit->append("");
        QString picPath=QDir::currentPath()+"/temp.png";

        qDebug()<<"picture saved in "<<picPath;

        QUrl Uri (QString("file://%1").arg (picPath));
        QImage image = QImageReader(picPath).read();
        qDebug()<<image.isNull();
        QTextDocument * textDocument = messageEdit->document();
        textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant(image));
        QTextCursor cursor = messageEdit->textCursor();
        QTextImageFormat imageFormat;
        if(trueImage->isChecked()){
            imageFormat.setWidth(image.width());
            imageFormat.setHeight(image.height());
        }
        else{
            if(image.height()>200){

                imageFormat.setWidth((double)image.width()/image.height()*200);
                imageFormat.setHeight(200);
            }
            else{
                imageFormat.setWidth(image.width());
                imageFormat.setHeight(image.height());
            }
        }
        imageFormat.setName(Uri.toString());
        cursor.insertImage(imageFormat);
        QFile::remove(picPath);
    }
    else{
        qDebug()<<"error";
    }

}
