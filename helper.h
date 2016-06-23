#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <QString>
#include "cJSON.h"

class Helper
{
private:
    Helper();
    static Helper *helper;

public:
    static Helper *getInstance();
    std::string getfromJson(std::string textJson, const char *name);
};

#endif // HELPER_H
