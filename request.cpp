#include "request.h"

Request::Request()
{
    this->_m_book = nullptr;
    this->_m_amount = 0;
    this->_m_time = 0;
    this->_m_id = 0;
    this->_m_curDay = 0;
}

Request::Request(Book *book, int amount, int time, int id, int curDay)
{
    this->_m_book = book;
    this->_m_amount = amount;
    this->_m_time = time;
    this->_m_id = id;
    this->_m_curDay = curDay;
}

Request::~Request()
{

}

int Request::getAmount() const
{
    return this->_m_amount;
}

int Request::getTime() const
{
    return this->_m_time;
}

int Request::getId() const
{
    return this->_m_id;
}

int Request::getCurDay() const
{
    return this->_m_curDay;
}

Book *Request::getBook()
{
    return this->_m_book;
}

void Request::setTime(int days)
{
    this->_m_time = days;
}
