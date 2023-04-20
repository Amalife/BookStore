#ifndef REQUEST_H
#define REQUEST_H

#include "book.h"

class Request
{
public:
    Request();
    Request(Book *book, int amount, int time, int id, int curDay);
    ~Request();

    int getAmount() const;
    int getTime() const;
    int getId() const;
    int getCurDay() const;
    Book *getBook();

    void setTime(int days);

private:
    Book *_m_book;
    int _m_amount;
    int _m_time;
    int _m_id;
    int _m_curDay;
};

#endif // REQUEST_H
