#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "../stdafx.h"
#include "../ui.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    bool isLogin();

protected:
    //绘制窗体
    void paintEvent(QPaintEvent *event);
    //鼠标监听
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //键盘监听
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_loginButton_clicked();
    void on_regButton_clicked();
    void on_exitButton_clicked();
    void on_cancelButton_clicked();

private:
    void exit();
    Ui::LoginWindow *ui;
    bool login;
    QPoint move_point;
    bool mouse_press;
};

#endif // LOGINWINDOW_H
