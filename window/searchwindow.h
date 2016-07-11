#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "stdafx.h"
#include "button/closebutton.h"

class SearchWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SearchWindow(QWidget *parent = 0);
    void showSearchUser(QString searchName);

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


signals:

private:
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QLabel *resultLabel;
    QPushButton *addButton;
    CloseButton *closeButton;
    bool pressed;
    QPoint place;

private slots:
    void on_searchButton_clicked();
    void on_addButton_clicked();
    void on_closeButton_clicked();

};

#endif // SEARCHWINDOW_H
