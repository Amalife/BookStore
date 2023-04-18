#include "instance.h"

Instance::Instance()
{
    this->_m_book = nullptr;
    this->_m_amount = 0;
}

Instance::Instance(const std::string &name, const std::string &author, const std::string &editor, int price, int margPrice, int amount)
{
    this->_m_book = new Book(name, author, editor, price, margPrice);
    this->_m_amount = amount;
}

Instance::~Instance()
{
    delete this->_m_book;
}

int Instance::getAmount() const
{
    return this->_m_amount;
}

void Instance::setAmount(int amount)
{
    this->_m_amount = amount;
}

Book *Instance::getBook() const
{
    return this->_m_book;
}
