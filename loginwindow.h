#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

    void on_regButton_clicked();

    void on_exitButton_clicked();

    void on_cancelButton_clicked();

private:
    QPoint move_point;
    bool mouse_press;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
