#include "request.h"

Request::Request()
{
    this->_m_book = nullptr;
    this->_m_amount = 0;
    this->_m_time = 0;
}

Request::Request(Book *book, int amount, int time)
{
    this->_m_book = book;
    this->_m_amount = amount;
    this->_m_time = time;
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

Book *Request::getBook()
{
    return this->_m_book;
}

void Request::setTime(int days)
{
    this->_m_time = days;
}
