#include "traymenu.h"

TrayMenu::TrayMenu(QWidget *parent):
    QMenu(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
    exitAction = new QAction(this);
    exitAction->setText("exit");
    this->addAction(exitAction);
}

TrayMenu::~TrayMenu()
{

}

void TrayMenu::paintEvent(QPaintEvent *event)
{
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
//    p.setRenderHint(QPainter::Antialiasing);
    int arcR = 5;
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
