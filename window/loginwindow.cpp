#include "stdafx.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "tray/trayicon.h"
#include "message/loginmessage.h"
#include "cJSON.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow),
    client(CommonElements::getInstance()->client),
    login(false),
    mouse_press(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
    setMouseTracking(true);
    ui->cancelButton->hide();
    ui->loginLabel->hide();
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient2()));
}

void LoginWindow::readClient2()
{
    QString str = client->readAll();
    cJSON *json = cJSON_Parse(str.toStdString().c_str());
    cJSON *json_status = cJSON_GetObjectItem(json, "status");
    std::string status = json_status->valuestring;
    cJSON_Delete(json);
    if (status == "true")
    {

    }
    else
    {
        this->on_cancelButton_clicked();
        ui->passwordEdit->setText("");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    ui->loginButton->hide();
    ui->usernameEdit->hide();
    ui->passwordEdit->hide();
    ui->regButton->hide();
    ui->exitButton->hide();
    ui->loginLabel->show();
    ui->cancelButton->show();
    ui->cancelButton->setFocus();

    //    QEventLoop eventloop;
    //    QTimer::singleShot(5000, &eventloop, SLOT(quit()));
    //    eventloop.exec();

    std::string username = ui->usernameEdit->text().toStdString();
    std::string password = ui->passwordEdit->text().toStdString();

    loginMessage lm(username, password);
    client->write(lm.getJsonString().c_str());
    //    login = true;

}

void LoginWindow::on_regButton_clicked()
{

}

void LoginWindow::on_exitButton_clicked()
{
    this->exit();
}

void LoginWindow::on_cancelButton_clicked()
{
    ui->loginButton->show();
    ui->regButton->show();
    ui->exitButton->show();
    ui->usernameEdit->show();
    ui->passwordEdit->show();
    ui->loginLabel->hide();
    ui->cancelButton->hide();
    ui->loginButton->setFocus();
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        move_point = event->pos();
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_press = false;
        move_point = event->pos();
    }
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_press)
    {
        QPoint move_pos = event->globalPos();
        this->move(move_pos-move_point);
    }
}

void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        this->on_loginButton_clicked();
        break;
    default:
        break;
    }
}

void LoginWindow::keyReleaseEvent(QKeyEvent *event)
{

}

bool LoginWindow::isLogin()
{
    return login;
}

void LoginWindow::exit()
{
    QMessageBox msgBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint| (msgBox.windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));

    msgBox.addButton("是", QMessageBox::AcceptRole);
    msgBox.addButton("否", QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
    {
        std::exit(0);
    }
}

void LoginWindow::paintEvent(QPaintEvent *event)
{
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing);
    int arcR = 10;
    QRect rect = this->rect();
    QPainterPath path;
    path.moveTo(arcR, 0);
    path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
    path.lineTo(0, rect.height() - arcR);
    path.arcTo(0, rect.height() - arcR * 2, arcR * 2, arcR * 2, 180.0f, 90.0f);
    path.lineTo(rect.width() - arcR, rect.height());
    path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2, arcR * 2, arcR * 2, -90.0f, 90.0f);
    path.lineTo(rect.width(), arcR);
    path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
    path.lineTo(arcR, 0);
    p.drawPath(path);
    p.fillPath(path, QBrush(Qt::red));
    setMask(bmp);
}
