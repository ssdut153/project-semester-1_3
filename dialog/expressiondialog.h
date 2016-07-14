#ifndef EXPRESSIONDIALOG_H
#define EXPRESSIONDIALOG_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "window/chatwindow.h"

class ExpressionDialog: public QDialog
{
    Q_OBJECT

public:
    explicit ExpressionDialog(ChatWindow *parent);

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void addExpression(QString exp);
    QPushButton *huajiButton;
    QPushButton *dahanButton;
    QPushButton *fennuButton;
    QPushButton *guaiqiaoButton;
    QPushButton *hechaButton;
    QPushButton *kaixinButton;
    QPushButton *penshuiButton;
    QPushButton *weixiaoButton;
    QPushButton *yinxianButton;
    QPushButton *cancelButton;
    ChatWindow *chatwindow;
    bool pressed;
    QPoint place;

private slots:
    void on_cancelButton_clicked();
    void on_huajiButton_clicked();
    void on_dahanButton_clicked();
    void on_fennuButton_clicked();
    void on_guaiqiaoButton_clicked();
    void on_hechaButton_clicked();
    void on_kaixinButton_clicked();
    void on_penshuiButton_clicked();
    void on_weixiaoButton_clicked();
    void on_yinxianButton_clicked();

};

#endif // EXPRESSIONDIALOG_H
