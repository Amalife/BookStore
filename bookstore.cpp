#include "bookstore.h"
#include "ui_bookstore.h"

#include <iostream>

BookStore::BookStore(QWidget *parent, const std::string &booksFile)
    : QWidget(parent)
    , ui(new Ui::BookStore)
    , _m_booksFile(booksFile)
{
    ui->setupUi(this);
    this->_m_curDay = 0;

    connect(ui->nextButton, &QPushButton::clicked, this, &BookStore::slotButtonClicked);
    connect(this, &BookStore::nextButtonClicked, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->deliveryFrom, QOverload<int>::of(&QSpinBox::valueChanged), this, &BookStore::slotSpinBoxChange);
}

BookStore::~BookStore()
{
    delete ui;
    delete this->_m_storage;
    delete this->_m_storeTable;
}

void BookStore::slotButtonClicked()
{
    this->_m_initStore = ui->initStore->value();
    this->_m_nDay = ui->period->value();
    this->_m_delivery[0] = ui->deliveryFrom->value();
    this->_m_delivery[1] = ui->deliveryTo->value();
    this->_m_margin = ui->margin->value();

    this->_m_storage = new Storage(this->_m_booksFile, this->_m_margin);
    std::map<std::string, Book*> stor = this->_m_storage->getStorage();
    int count = stor.size();
    int first = this->_m_initStore / count;
    int addFlag = this->_m_initStore % count;
    int i = 0;

    for (const auto& [key, val] : stor)
    {
        if (i < addFlag)
            val->setAmount(first + 1);
        else
            val->setAmount(first);
        //std::cout << '[' << key << "] = " << val->getAmount() << std::endl;
        i++;
    }
    this->_m_storeTable = new StoreTableModel();
    this->_m_storeTable->populateData(stor);
    ui->store->setModel(this->_m_storeTable);
    ui->store->horizontalHeader()->setVisible(true);
    emit nextButtonClicked(1);
}

void BookStore::slotSpinBoxChange(int val)
{
    ui->deliveryTo->setMinimum(val+1);
}
