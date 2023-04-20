#ifndef ORDER_H
#define ORDER_H

#include "book.h"

const int ORDERED = 0;
const int DELAYED = 1;
const int DELIVERED = 2;

class Order
{
public:
    Order();
    Order(const std::string &name, const std::string &phone, Book *book, int amount, int id, int curDay);
    ~Order();

    const std::string &getName() const;
    const std::string &getPhone() const;
    int getAmount() const;
    int getStatus() const;
    int getId() const;
    int getCurDay() const;
    Book *getBook();

    void setStatus(int status);

private:
    const std::string _m_name;
    const std::string _m_phone;
    Book *_m_book;
    int _m_amount;
    int _m_status;
    int _m_id;
    int _m_curDay;

};

#endif // ORDER_H
