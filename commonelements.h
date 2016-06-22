#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include "tray/trayicon.h"

class CommonElements
{

private:
    static CommonElements *instance;
    CommonElements();

public:
    ~CommonElements();
    TrayIcon *trayIcon;
    static CommonElements *getInstance();

};

#endif // COMMONELEMENTS_H
