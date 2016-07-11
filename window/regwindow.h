#ifndef REGWINDOW_H
#define REGWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "button/closebutton.h"

class RegWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit RegWindow(QWidget *parent = 0);
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
    void paintEvent(QPaintEvent *event);

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

signals:

};

#endif // REGWINDOW_H
