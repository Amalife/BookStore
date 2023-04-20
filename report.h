#ifndef REPORT_H
#define REPORT_H


class Report
{
public:
    Report();
    ~Report();

    int getSoldBooks() const;
    int getMadeOrders() const;
    int getMadeRequest() const;
    int getIncome() const;
    int getConsum() const;

    void setSoldBooks(int soldBooks);
    void setMadeOrders(int madeOrders);
    void setMadeRequest(int madeRequets);
    void setIncome(int income);
    void setConsum(int consum);

private:
    int _m_soldBooks;
    int _m_madeOrders;
    int _m_madeRequest;
    int _m_income;
    int _m_consum;
};

#endif // REPORT_H
