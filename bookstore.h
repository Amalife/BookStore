#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QWidget>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "storage.h"
#include "request.h"
#include "order.h"
#include "storetablemodel.h"
#include "reqtablemodel.h"
#include "ordtablemodel.h"
#include "report.h"
#include "reportwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BookStore; }
QT_END_NAMESPACE

class BookStore : public QWidget
{
    Q_OBJECT

public:
    BookStore(const std::string &booksFile, const std::string &clientFile, QWidget *parent = nullptr);
    ~BookStore();

    void makeNamesPhones(const std::string &clientsFile);
    void checkRequests();
    void reduceReqDays();
    void createOrders();
    void acceptOrders();
    void removeOrders();
    void addRequests();
    bool checkDiffOrd(Book *book, int diff);

signals:
    void nextButtonClicked(int);

private slots:
    void slotButtonClicked();
    void slotSpinBoxDeliv(int val);
    void slotSpinBoxCount(int val);
    void slotSpinBoxBooks(int val);
    void slotNextButtonClicked();

private:
    Ui::BookStore *ui;
    int _m_initStore;
    int _m_nDay;
    int _m_delivery[2];
    int _m_countOrds[2];
    int _m_countBooks[2];
    int _m_margin;

    int _m_nClients;
    int _m_deleteFlag;

    int _m_curDay;
    const std::string _m_booksFile;
    const std::string _m_clientsFile;

    std::string *_m_cNames;
    std::string *_m_cPhones;

    Storage *_m_storage;
    std::vector<Request *> _m_reqs;
    std::vector<Order *> _m_ords;

    StoreTableModel *_m_storeTable;
    ReqTableModel *_m_reqTable;
    OrdTableModel *_m_ordTable;

    Report *_m_report;
    ReportWindow *_m_reportWindow;
};
#endif // BOOKSTORE_H
