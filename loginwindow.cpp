#include "stdafx.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow),
    login(false),
    mouse_press(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    ui->cancelButton->hide();
    ui->loginLabel->hide();
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

    QEventLoop eventloop;
    QTimer::singleShot(5000, &eventloop, SLOT(quit()));
    eventloop.exec();

    login = true;

}

void LoginWindow::on_regButton_clicked()
{

}

void LoginWindow::on_exitButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, "Warning", "您真的要退出吗", 0, this);
    msgBox.addButton("Yes", QMessageBox::AcceptRole);
    msgBox.addButton("No", QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        std::exit(0);
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

void LoginWindow::on_cancelButton_clicked()
{
    ui->loginButton->show();
    ui->regButton->show();
    ui->exitButton->show();
    ui->usernameEdit->show();
    ui->passwordEdit->show();
    ui->loginLabel->hide();
    ui->cancelButton->hide();
}

bool LoginWindow::isLogin()
{
    return login;
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
    path.lineTo(0, rect.height() - arcR * 2);
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
