#include "commonelements.h"

CommonElements::CommonElements():
    trayIcon(new TrayIcon)
{

}

CommonElements::~CommonElements()
{
    delete trayIcon;
}

CommonElements *CommonElements::instance = 0;

CommonElements *CommonElements::getInstance()
{
    if(instance == 0)
    {
        instance = new CommonElements;
    }
    return instance;
}
