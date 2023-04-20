#include "storage.h"

Storage::Storage(const std::string &bookFile, int margin)
{
    std::string line;
    std::string delim = " ";
    std::string tokens[4];
    int i;
    int j = 0;
    size_t pos;
    int price;
    int margPrice;

    this->_m_input.open(bookFile.c_str(), std::ios::in);
    if (!_m_input)
        std::cout << "Error: cannot open file\n";
    int count = std::count(std::istreambuf_iterator<char>(this->_m_input),
                            std::istreambuf_iterator<char>(), '\n');
    this->_m_input.seekg(0, std::ios::beg);
    this->_m_nBooks = count;
    this->_m_stor = new Instance*[count];
    while (std::getline(this->_m_input, line))
    {
        i = 0;
        //pos = 0;
        while ((pos = line.find(delim)) != std::string::npos)
        {
            tokens[i] = line.substr(0, pos);
            line.erase(0, pos + delim.length());
            i++;
        }
        tokens[i] = line;
        price = std::atoi(tokens[3].c_str());
        margPrice = price + int(float(price) * 0.01 * float(margin));
        this->_m_stor[j] = new Instance(tokens[0], tokens[1], tokens[2], price, margPrice, 0);
        j++;
    }
    this->_m_input.close();
}

Storage::~Storage()
{
    for (int i = 0; i < this->getNBooks(); i++)
        delete this->_m_stor[i];
    delete[] this->_m_stor;
}

Instance **Storage::getStorage()
{
    return this->_m_stor;
}

int Storage::getNBooks() const
{
    return this->_m_nBooks;
}

void Storage::incDecAmount(Book *book, int amount)
{
    int id = 0;

    while (book != this->_m_stor[id]->getBook())
        id++;
    this->_m_stor[id]->setAmount(this->_m_stor[id]->getAmount() + amount);
}

bool Storage::canSell(Order *ord)
{
    Book *book;
    int id = 0;

    book = ord->getBook();
    while (book != this->_m_stor[id]->getBook())
        id++;
    if (this->_m_stor[id]->getAmount() - ord->getAmount() >= 0)
        return true;
    return false;
}

int Storage::getAmountBook(Book *book)
{
    for (int i = 0; i < this->_m_nBooks; i++)
        if (book == this->_m_stor[i]->getBook())
            return this->_m_stor[i]->getAmount();
    return 0;
}
