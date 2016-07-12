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
    expressButton(new QPushButton(this)),
    filButton(new QPushButton(this)),
    closeButton(new CloseButton(this)),
    trueImage(new QRadioButton(this)),
    manager(0),
    recmanager(0)
{

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMinimumSize(800, 600);
    this->setMaximumSize(800, 600);

    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, 600));
    linearGradient.setColorAt(0, QColor(133, 218, 223));
    linearGradient.setColorAt(1, QColor(255, 255, 255));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(linearGradient));
    this->setPalette(palette);

    this->setWindowTitle(this->friendName);

    this->sendButton->setText("发送");
    this->picButton->setText("图");
    this->trueImage->setText("显示原图");

    this->trueImage->setChecked(false);

    this->messageEdit->setReadOnly(true);

    this->messageEdit->setGeometry(50, 40, 700, 330);
    this->sendEdit->setGeometry(50, 420, 700, 120);
    this->sendButton->setGeometry(710, 550, 60, 30);
    this->picButton->setGeometry(90, 380, 30, 30);
    this->expressButton->setGeometry(50, 380, 30, 30);
    this->filButton->setGeometry(130, 380, 30, 30);
    this->closeButton->setGeometry(770, 0, 30, 30);
    this->trueImage->setGeometry(350, 550, 80, 30);

    this->expressButton->setIcon(QIcon(":/images/expression"));
    this->expressButton->setIconSize(QSize(30, 30));
    this->filButton->setIcon(QIcon(":/images/file"));
    this->expressButton->setIconSize(QSize(30, 30));

    connect(this->sendButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked()));
    connect(this->picButton, SIGNAL(clicked()), this, SLOT(on_picButton_clicked()));
    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(on_closeButton_clicked()));
    connect(this->expressButton, SIGNAL(clicked()), this, SLOT(on_expressButton_clicked()));
    connect(this->filButton, SIGNAL(clicked()), this, SLOT(on_filButton_clicked()));

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
        this->messageEdit->append(this->username + " " + time);
        this->messageEdit->append(content);
        Database *db = Database::getInstance(this->username);
        db->addMessage(this->friendName, 1, time, content);
    }
}

void ChatWindow::on_picButton_clicked()
{
    picPath = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.gif)"));
    if (!picPath.isNull())
    {
        QImage *img = new QImage;
        if(!(img->load(picPath)))
        {
            QMessageBox::information(this, "打开图像失败", "打开图像失败!");
            delete img;
            return;
        }
        QFile Image(picPath);
        Image.open(QIODevice::ReadOnly);

        QByteArray by_img=Image.readAll();
        Image.close();
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
        delete img;
    }
}

void ChatWindow::receivePic(imageMessage im)
{
    recmanager = new QNetworkAccessManager(this);
    connect(recmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReceiveFinished(QNetworkReply*)));
    QString url="http://upload.ssdut153.cn/chatpic/"+im.FromUserName+"_"+im.ToUserName+"_"+im.CreateTime+".png";

    QUrl u(url);
    recmanager->get(QNetworkRequest(u));
    this->sendButton->setDisabled(true);
    this->picButton->setDisabled(true);

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
    }
    else
    {
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->messageEdit->append("can't connect to sever.");
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
        QString picPath=QDir::currentPath()+"/temp.png";

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
    }
    else
    {
        this->sendButton->setDisabled(false);
        this->picButton->setDisabled(false);
        this->messageEdit->append("can't connect to sever.");
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
    if(manager!=0)
        delete manager;
    if(recmanager!=0)
        delete recmanager;
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

}

void ChatWindow::on_filButton_clicked()
{

}
