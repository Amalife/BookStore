#include "report.h"

Report::Report()
{
    this->_m_soldBooks = 0;
    this->_m_madeOrders = 0;
    this->_m_madeRequest = 0;
    this->_m_income = 0;
    this->_m_consum = 0;
}

Report::~Report()
{

}

int Report::getSoldBooks() const
{
    return this->_m_soldBooks;
}

int Report::getMadeOrders() const
{
    return this->_m_madeOrders;
}

int Report::getMadeRequest() const
{
    return this->_m_madeRequest;
}

int Report::getIncome() const
{
    return this->_m_income;
}

int Report::getConsum() const
{
    return this->_m_consum;
}

void Report::setSoldBooks(int soldBooks)
{
    this->_m_soldBooks = soldBooks;
}

void Report::setMadeOrders(int madeOrders)
{
    this->_m_madeOrders = madeOrders;
}

void Report::setMadeRequest(int madeRequets)
{
    this->_m_madeRequest = madeRequets;
}

void Report::setIncome(int income)
{
    this->_m_income = income;
}

void Report::setConsum(int consum)
{
    this->_m_consum = consum;
}
