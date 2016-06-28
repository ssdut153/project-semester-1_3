#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "ui.h"
#include "stdafx.h"

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
