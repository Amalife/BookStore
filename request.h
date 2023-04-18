#ifndef REQUEST_H
#define REQUEST_H

#include "book.h"

class Request
{
public:
    Request();
    Request(Book *book, int amount, int time);
    ~Request();

    int getAmount() const;
    int getTime() const;
    Book *getBook();

    void setTime(int days);

private:
    Book *_m_book;
    int _m_amount;
    int _m_time;
};

#endif // REQUEST_H
