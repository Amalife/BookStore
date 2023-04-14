#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include "book.h"

class Storage
{
public:
    Storage(const std::string &bookFile, int margin);
    ~Storage();

    const std::map<std::string, Book*> &getStorage() const;

private:
    std::map<std::string, Book*> _m_stor;
    std::ifstream _m_input;
};

#endif // STORAGE_H
