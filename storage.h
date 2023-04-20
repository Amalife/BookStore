#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "instance.h"
#include "request.h"
#include "order.h"

class Storage
{
public:
    Storage(const std::string &bookFile, int margin);
    ~Storage();

    Instance **getStorage();
    bool canSell(Order *ord);
    void incDecAmount(Book *book, int amount);
    int getAmountBook(Book *book);
    int getNBooks() const;

private:
    Instance **_m_stor;
    std::ifstream _m_input;
    int _m_nBooks;
};
#endif // STORAGE_H
