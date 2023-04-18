#include "bookstore.h"
#include "ui_bookstore.h"

#include <iostream>

BookStore::BookStore(const std::string &booksFile, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookStore)
    , _m_booksFile(booksFile)
{
    ui->setupUi(this);

    connect(ui->setupButton, &QPushButton::clicked, this, &BookStore::slotButtonClicked);
    connect(this, &BookStore::nextButtonClicked, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->deliveryFrom, QOverload<int>::of(&QSpinBox::valueChanged), this, &BookStore::slotSpinBoxChange);
    connect(ui->exitButton_1, &QPushButton::pressed, this, &BookStore::close);
    connect(ui->exitButton_2, &QPushButton::pressed, this, &BookStore::close);
    connect(ui->startButton, &QPushButton::pressed, this, &BookStore::slotNextButtonClicked);
}

BookStore::~BookStore()
{
    delete ui;
    delete this->_m_storage;
    delete this->_m_storeTable;
    delete this->_m_reqTable;
    this->_m_reqs.clear();
}

void BookStore::slotNextButtonClicked()
{
    if (ui->currentDay->text() == "0")
        ui->startButton->setText(QString("Next day"));
    this->_m_reqs.push_back(new Request(this->_m_storage->getStorage()[0]->getBook(), 7, 2));
    this->_m_reqTable->populateData(this->_m_reqs);
    this->_m_curDay++;
    ui->currentDay->setText(QString::fromUtf8(std::to_string(this->_m_curDay).c_str()));
}

void BookStore::slotButtonClicked()
{
    this->_m_initStore = ui->initStore->value();
    this->_m_nDay = ui->period->value();
    this->_m_delivery[0] = ui->deliveryFrom->value();
    this->_m_delivery[1] = ui->deliveryTo->value();
    this->_m_margin = ui->margin->value();
    this->_m_curDay = 0;

    this->_m_storage = new Storage(this->_m_booksFile, this->_m_margin);
    Instance **stor = this->_m_storage->getStorage();
    int count = 10;
    int first = this->_m_initStore / count;
    int addFlag = this->_m_initStore % count;
    int i = 0;

    for (int k = 0; k < 10; k++)
    {
        if (i < addFlag)
            (*stor[k]).setAmount(first + 1);
        else
            (*stor[k]).setAmount(first);
        //std::cout << '[' << key << "] = " << val->getAmount() << std::endl;
        i++;
    }

    this->_m_storeTable = new StoreTableModel();
    this->_m_storeTable->populateData(stor);
    ui->store->setModel(this->_m_storeTable);
    ui->store->horizontalHeader()->setVisible(true);

    this->_m_reqTable = new ReqTableModel();
    ui->requests->setModel(this->_m_reqTable);
    ui->requests->horizontalHeader()->setVisible(true);

    ui->endDay->setText(QString::fromUtf8(std::to_string(this->_m_nDay).c_str()));
    emit nextButtonClicked(1);
}

void BookStore::slotSpinBoxChange(int val)
{
    ui->deliveryTo->setMinimum(val+1);
}
