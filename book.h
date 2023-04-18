#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
public:
    Book(const std::string &name, const std::string &author, const std::string &editor, int price, int margPrice);
    ~Book();

    const std::string &getName() const;
    const std::string &getAuthor() const;
    const std::string &getEditor() const;
    int getPrice() const;
    int getMargPrice() const;

private:
    const std::string _m_name;
    const std::string _m_author;
    const std::string _m_editor;
    int         _m_price;
    int         _m_margPrice;
};

#endif // BOOK_H
