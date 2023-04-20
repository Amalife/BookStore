#include "order.h"

Order::Order()
{
    this->_m_book = nullptr;
    this->_m_amount = 0;
    this->_m_status = ORDERED;
    this->_m_id = 0;
    this->_m_curDay = 0;
}

Order::Order(const std::string &name, const std::string &phone, Book *book, int amount, int id, int curDay):
    _m_name(name),
    _m_phone(phone)
{
    this->_m_book = book;
    this->_m_amount = amount;
    this->_m_status = ORDERED;
    this->_m_id = id;
    this->_m_curDay = curDay;
}

Order::~Order()
{

}

const std::string &Order::getName() const
{
    return this->_m_name;
}

const std::string &Order::getPhone() const
{
    return this->_m_phone;
}

int Order::getAmount() const
{
    return this->_m_amount;
}

int Order::getStatus() const
{
    return this->_m_status;
}

int Order::getId() const
{
    return this->_m_id;
}

int Order::getCurDay() const
{
    return this->_m_curDay;
}

Book *Order::getBook()
{
    return this->_m_book;
}

void Order::setStatus(int status)
{
    this->_m_status = status;
}
