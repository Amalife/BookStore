#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QWidget>
#include <fstream>
#include <string>
#include <deque>

#include "storage.h"
#include "request.h"
#include "storetablemodel.h"
#include "reqtablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BookStore; }
QT_END_NAMESPACE

class BookStore : public QWidget
{
    Q_OBJECT

public:
    BookStore(const std::string &booksFile, QWidget *parent = nullptr);
    ~BookStore();

signals:
    void nextButtonClicked(int);

private slots:
    void slotButtonClicked();
    void slotSpinBoxChange(int val);
    void slotNextButtonClicked();

private:
    Ui::BookStore *ui;
    int _m_initStore;
    int _m_nDay;
    int _m_delivery[2];
    int _m_margin;

    int _m_curDay;
    const std::string _m_booksFile;
    const std::string _m_clientsFile;

    Storage *_m_storage;
    std::deque<Request *> _m_reqs;

    StoreTableModel *_m_storeTable;
    ReqTableModel *_m_reqTable;
};
#endif // BOOKSTORE_H
