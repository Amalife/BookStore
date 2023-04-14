#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QWidget>
#include <fstream>
#include <string>

#include "storage.h"
#include "storetablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BookStore; }
QT_END_NAMESPACE

class BookStore : public QWidget
{
    Q_OBJECT

public:
    BookStore(QWidget *parent = nullptr, const std::string &booksFile = nullptr);
    ~BookStore();

signals:
    void nextButtonClicked(int);

private slots:
    void slotButtonClicked();
    void slotSpinBoxChange(int val);

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
    StoreTableModel *_m_storeTable;
};
#endif // BOOKSTORE_H
