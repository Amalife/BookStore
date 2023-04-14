#include "storage.h"

Storage::Storage(const std::string &bookFile, int margin)
{
    std::string line;
    std::string delim = " ";
    std::string tokens[5];
    int i;
    size_t pos;
    int price;
    int margPrice;

    this->_m_input.open(bookFile.c_str(), std::ios::in);
    if (!_m_input)
        std::cout << "Error: cannot open file\n";
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
        price = std::atoi(tokens[4].c_str());
        margPrice = price + int(float(price) * 0.01 * float(margin));
        this->_m_stor[tokens[0]] = new Book(tokens[1], tokens[2], tokens[3], price, margPrice, 0);
    }
    this->_m_input.close();
}

Storage::~Storage()
{
    for (const auto& [key, val] : this->_m_stor)
        delete val;
}

const std::map<std::string, Book*> &Storage::getStorage() const
{
    return this->_m_stor;
}
