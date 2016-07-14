#ifndef REGDIALOG_H
#define REGDIALOG_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "button/closebutton.h"

class RegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegDialog(QWidget *parent = 0);
    QLabel *getMessageLabel();
    QPushButton *getRegButton();
    QString getUsername();
    QString getPassword();

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel *messageLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit_1;
    QLineEdit *passwordEdit_2;
    QPushButton *regButton;
    CloseButton *closeButton;
    QString username;
    QString password;
    bool pressed;
    QPoint place;

private slots:
    void on_regButton_clicked();
    void on_closeButton_clicked();

};

#endif // REGDIALOG_H
