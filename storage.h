#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>
#include <iostream>
#include "instance.h"

class Storage
{
public:
    Storage(const std::string &bookFile, int margin);
    ~Storage();

    Instance **getStorage();

private:
    Instance *_m_stor[10];
    std::ifstream _m_input;
};

#endif // STORAGE_H
