#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QMainWindow>

namespace Ui {
class RegWindow;
}

class RegWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = 0);
    ~RegWindow();

private:
    Ui::RegWindow *ui;
};

#endif // REGWINDOW_H
