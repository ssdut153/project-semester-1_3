#include "dialog/searchdialog.h"
#include "commonelements.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    searchEdit(new QLineEdit(this)),
    searchButton(new QPushButton(this)),
    resultLabel(new QLabel(this)),
    addButton(new QPushButton(this)),
    closeButton(new CloseButton(this)),
    messageLabel(new QLabel(this))
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setMaximumSize(400, 280);
    this->setMinimumSize(400, 280);

    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, 280));
    linearGradient.setColorAt(0, QColor(133, 218, 223));
    linearGradient.setColorAt(1, QColor(255, 255, 255));

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(linearGradient));
    this->setPalette(palette);

    this->searchButton->setText("查询");
    this->addButton->setText("添加");
    this->messageLabel->setText("<span style=\"color: red;\">该用户不存在</span>");

    this->searchEdit->setGeometry(35, 60, 200, 30);
    this->searchButton->setGeometry(278, 60, 60, 30);
    this->resultLabel->setGeometry(36, 110, 150, 30);
    this->addButton->setGeometry(278, 110, 60, 30);
    this->closeButton->setGeometry(370, 0, 30, 30);
    this->messageLabel->setGeometry(36, 110, 150, 30);

    this->searchEdit->setStyleSheet("border:none;");

    this->resultLabel->hide();
    this->addButton->hide();
    this->messageLabel->hide();

    connect(this->searchButton, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));
    connect(this->addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(on_closeButton_clicked()));

}

void SearchDialog::on_searchButton_clicked()
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

void SearchDialog::on_addButton_clicked()
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

void SearchDialog::showSearchUser(QString searchName)
{
    if(searchName == "")
    {
        this->messageLabel->show();
    }
    else
    {
        this->resultLabel->setText(searchName);
        this->resultLabel->show();
        this->addButton->show();
    }
}

void SearchDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    this->searchEdit->clear();
    this->resultLabel->clear();
    this->resultLabel->hide();
    this->addButton->hide();
}

void SearchDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        this->on_searchButton_clicked();
        break;
    case Qt::Key_Escape:
        this->on_closeButton_clicked();
        break;
    }
}

void SearchDialog::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void SearchDialog::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void SearchDialog::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        this->move(this->x() + temp.x() - this->place.x(), this->y() + temp.y() - this->place.y());
    }
}

void SearchDialog::on_closeButton_clicked()
{
    this->hide();
    this->searchEdit->clear();
    this->resultLabel->clear();
    this->resultLabel->hide();
    this->addButton->hide();
    this->messageLabel->hide();
}
