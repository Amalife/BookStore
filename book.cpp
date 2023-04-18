#include "book.h"

Book::Book(const std::string &name, const std::string &author, \
           const std::string &editor, int price, int margPrice):
    _m_name(name), _m_author(author), _m_editor(editor), _m_price(price), _m_margPrice(margPrice)
{

}

Book::~Book()
{

}

const std::string &Book::getName() const
{
    return this->_m_name;
}

const std::string &Book::getAuthor() const
{
    return this->_m_author;
}

const std::string &Book::getEditor() const
{
    return this->_m_editor;
}

int Book::getPrice() const
{
    return this->_m_price;
}

int Book::getMargPrice() const
{
    return this->_m_margPrice;
}
