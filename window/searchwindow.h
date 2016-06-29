#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "ui.h"
#include "stdafx.h"
#include "search.h"

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();
    void showSearchUser(QString searchName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_searchButton_clicked();
    void on_addButton_clicked();

private:
    Ui::SearchWindow *ui;
    QVector<QLabel *> labels;
};

#endif // SEARCHWINDOW_H
