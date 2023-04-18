#ifndef INSTANCE_H
#define INSTANCE_H

#include "book.h"

class Instance
{
public:
    Instance();
    Instance(const std::string &name, const std::string &author, const std::string &editor, int price, int margPrice, int amount);
    ~Instance();

    int getAmount() const;
    Book *getBook() const;

    void setAmount(int amount);

private:
    Book *_m_book;
    int _m_amount;

};

#endif // INSTANCE_H
