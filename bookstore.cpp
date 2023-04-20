#include "bookstore.h"
#include "ui_bookstore.h"

#include <iostream>

BookStore::BookStore(const std::string &booksFile, const std::string &clientsFile, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookStore)
    , _m_booksFile(booksFile)
    , _m_clientsFile(clientsFile)
{
    ui->setupUi(this);
    srand((unsigned) time(nullptr));
    this->_m_deleteFlag = 0;
    this->_m_reportWindow = new ReportWindow();

    connect(ui->setupButton, &QPushButton::clicked, this, &BookStore::slotButtonClicked);
    connect(this, &BookStore::nextButtonClicked, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(ui->deliveryFrom, QOverload<int>::of(&QSpinBox::valueChanged), this, &BookStore::slotSpinBoxDeliv);
    connect(ui->ordNumFrom, QOverload<int>::of(&QSpinBox::valueChanged), this, &BookStore::slotSpinBoxCount);
    connect(ui->ordBooksFrom, QOverload<int>::of(&QSpinBox::valueChanged), this, &BookStore::slotSpinBoxBooks);
    connect(ui->exitButton_1, &QPushButton::pressed, this, &BookStore::close);
    connect(ui->exitButton_2, &QPushButton::pressed, this, &BookStore::close);
    connect(ui->startButton, &QPushButton::pressed, this, &BookStore::slotNextButtonClicked);
    connect(ui->reportButton, &QPushButton::pressed, this->_m_reportWindow, &ReportWindow::show);
}

BookStore::~BookStore()
{
    delete ui;
    delete this->_m_reportWindow;
    if (this->_m_deleteFlag)
    {
        delete this->_m_storage;
        delete this->_m_storeTable;
        delete this->_m_reqTable;
        delete this->_m_ordTable;
        this->_m_reqs.clear();
        this->_m_ords.clear();
        delete[] this->_m_cNames;
        delete[] this->_m_cPhones;
        delete this->_m_report;
    }
}

void BookStore::slotNextButtonClicked()
{
    if (ui->currentDay->text() == "0")
    {
        ui->startButton->setText(QString("Next day"));
        ui->labelProc->setText(QString("Process is running"));
    }

    this->checkRequests();

    this->createOrders();
    this->acceptOrders();
    //this->addRequests();

    this->_m_ordTable->populateData(this->_m_ords);
    this->_m_reqTable->populateData(this->_m_reqs);
    this->_m_storeTable->populateData(this->_m_storage->getStorage(), this->_m_storage->getNBooks());

    this->reduceReqDays();

    this->_m_curDay++;
    ui->currentDay->setText(QString::fromUtf8(std::to_string(this->_m_curDay).c_str()));

    this->removeOrders();
    if (ui->currentDay->text().toInt() == this->_m_nDay)
    {
        ui->startButton->setEnabled(false);
        ui->labelProc->setText(QString("Process is finished"));
        ui->reportButton->setFlat(false);
        ui->reportButton->setText(QString("Show report"));
        ui->reportButton->setStyleSheet("QPushButton { background-color: orange }");
        ui->reportButton->setEnabled(true);
        this->_m_reportWindow->setReport(this->_m_report);
    }
}

void BookStore::slotButtonClicked()
{
    this->_m_initStore = ui->initStore->value();
    this->_m_nDay = ui->period->value();
    this->_m_delivery[0] = ui->deliveryFrom->value();
    this->_m_delivery[1] = ui->deliveryTo->value();
    this->_m_countOrds[0] = ui->ordNumFrom->value();
    this->_m_countOrds[1] = ui->ordNumTo->value();
    this->_m_countBooks[0] = ui->ordBooksFrom->value();
    this->_m_countBooks[1] = ui->ordBooksTo->value();
    this->_m_margin = ui->margin->value();
    this->_m_curDay = 0;
    this->_m_deleteFlag = 1;

    this->_m_storage = new Storage(this->_m_booksFile, this->_m_margin);
    Instance **stor = this->_m_storage->getStorage();
    int count = this->_m_storage->getNBooks();
    int first = this->_m_initStore / count;
    int addFlag = this->_m_initStore % count;
    int i = 0;

    for (int k = 0; k < count; k++)
    {
        if (i < addFlag)
            (*stor[k]).setAmount(first + 1);
        else
            (*stor[k]).setAmount(first);
        //std::cout << '[' << key << "] = " << val->getAmount() << std::endl;
        i++;
    }

    this->makeNamesPhones(this->_m_clientsFile);

    this->_m_storeTable = new StoreTableModel();
    this->_m_storeTable->populateData(stor, this->_m_storage->getNBooks());
    ui->store->setModel(this->_m_storeTable);
    ui->store->horizontalHeader()->setVisible(true);

    this->_m_reqTable = new ReqTableModel();
    this->_m_reqTable->populateData(this->_m_reqs);
    ui->requests->setModel(this->_m_reqTable);
    ui->requests->horizontalHeader()->setVisible(true);

    this->_m_ordTable = new OrdTableModel();
    this->_m_ordTable->populateData(this->_m_ords);
    ui->orders->setModel(this->_m_ordTable);
    ui->orders->horizontalHeader()->setVisible(true);

    this->_m_report = new Report();
    ui->reportButton->setFlat(true);
    ui->reportButton->setEnabled(false);
    ui->reportButton->setText(QString(""));

    ui->endDay->setText(QString::fromUtf8(std::to_string(this->_m_nDay).c_str()));
    emit nextButtonClicked(1);
}

void BookStore::slotSpinBoxDeliv(int val)
{
    ui->deliveryTo->setMinimum(val+1);
}

void BookStore::slotSpinBoxCount(int val)
{
    ui->ordNumTo->setMinimum(val+1);
}

void BookStore::slotSpinBoxBooks(int val)
{
    ui->ordBooksTo->setMinimum(val+1);
}

void BookStore::makeNamesPhones(const std::string &clientsFile)
{
    std::string line;
    std::string delim = " ";
    std::string tokens[2];
    int i;
    int j = 0;
    size_t pos;
    std::ifstream input;

    input.open(clientsFile.c_str(), std::ios::in);
    if (!input)
        std::cout << "Error: cannot open file\n";
    int count = std::count(std::istreambuf_iterator<char>(input),
                            std::istreambuf_iterator<char>(), '\n');
    input.seekg(0, std::ios::beg);
    this->_m_nClients = count;
    this->_m_cNames = new std::string[count];
    this->_m_cPhones = new std::string[count];
    while (std::getline(input, line))
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
        this->_m_cNames[j] = tokens[0];
        this->_m_cPhones[j] = tokens[1];
        j++;
    }
    input.close();
}

bool isZeroDays(Request *req)
{
    if (req->getTime() == 0)
        return true;
    return false;
}

void BookStore::checkRequests()
{
    if (!this->_m_reqs.empty())
    {
        for (Request *elem : this->_m_reqs)
        {
            if (elem->getTime() == 0)
                this->_m_storage->incDecAmount(elem->getBook(), elem->getAmount());
        }
        this->_m_reqs.erase(std::remove_if(this->_m_reqs.begin(), this->_m_reqs.end(), isZeroDays), this->_m_reqs.end());

    }
}

void BookStore::reduceReqDays()
{
    if (!this->_m_reqs.empty())
        for (Request *elem : this->_m_reqs)
        {
            elem->setTime(elem->getTime() - 1);
        }
}

void BookStore::acceptOrders()
{
    int id = 1;
    if (!this->_m_ords.empty())
    {
        for (Order *elem : this->_m_ords)
        {
            if (this->_m_storage->canSell(elem))
            {
                this->_m_storage->incDecAmount(elem->getBook(), -elem->getAmount());
                elem->setStatus(DELIVERED);
                int days = this->_m_delivery[0] + (rand() % (this->_m_delivery[1] - this->_m_delivery[0] + 1));
                if (checkDiffOrd(elem->getBook(), 5))
                {
                    this->_m_reqs.push_back(new Request(elem->getBook(), 7, days, id, this->_m_curDay + 1));
                    id++;
                    this->_m_report->setMadeRequest(this->_m_report->getMadeRequest() + 1);
                    this->_m_report->setConsum(this->_m_report->getConsum() + (elem->getBook()->getPrice() * elem->getAmount()));
                }
                this->_m_report->setSoldBooks(this->_m_report->getSoldBooks() + elem->getAmount());
                this->_m_report->setMadeOrders(this->_m_report->getMadeOrders() + 1);
                this->_m_report->setIncome(this->_m_report->getIncome() + (elem->getBook()->getMargPrice() * elem->getAmount()));
            }
            else
            {
                elem->setStatus(DELAYED);
                int days = this->_m_delivery[0] + (rand() % (this->_m_delivery[1] - this->_m_delivery[0] + 1));
                if (checkDiffOrd(elem->getBook(), 0))
                {
                    this->_m_reqs.push_back(new Request(elem->getBook(), 7, days, id, this->_m_curDay + 1));
                    id++;
                    this->_m_report->setMadeRequest(this->_m_report->getMadeRequest() + 1);
                    this->_m_report->setConsum(this->_m_report->getConsum() + elem->getBook()->getPrice());
                }
            }
        }

    }
}

bool isDeliv(Order *ord)
{
    if (ord->getStatus() == DELIVERED)
        return true;
    return false;
}

void BookStore::removeOrders()
{
    if (!this->_m_ords.empty())
        this->_m_ords.erase(std::remove_if(this->_m_ords.begin(), this->_m_ords.end(), isDeliv), this->_m_ords.end());
}

bool BookStore::checkDiffOrd(Book *book, int diff)
{
    int ordAmount = 0;
    int reqAmount = 0;

    for (Order *elem : this->_m_ords)
    {
        if (book == elem->getBook() && (elem->getStatus() == DELAYED || elem->getStatus() == ORDERED))
            ordAmount += elem->getAmount();
    }

    for (Request *elem : this->_m_reqs)
    {
        if (book == elem->getBook())
            reqAmount += elem->getAmount();
    }

    if ((reqAmount - ordAmount + this->_m_storage->getAmountBook(book)) >= diff)
        return false;
    return true;
}

/*void BookStore::addRequests()
{
    Book *book;

    for (int i = 0; i < NBOOKS; i++)
    {
        book = this->_m_storage->getStorage()[i]->getBook();
        if (this->checkDiffOrd(book, 5))
        {
            int days = this->_m_delivery[0] + rand() % (this->_m_delivery[1] - this->_m_delivery[0] + 1);
            //this->_m_reqs.push_back(new Request(book, 7, days));
        }
    }
}*/

void BookStore::createOrders()
{
    int count;
    int amount;
    int cId;
    int bId;

    count = this->_m_countOrds[0] + (rand() % (this->_m_countOrds[1] - this->_m_countOrds[0] + 1));
    for (int i = 0; i < count; i++)
    {
        amount = this->_m_countBooks[0] + (rand() % (this->_m_countBooks[1] - this->_m_countBooks[0] + 1));
        cId = rand() % this->_m_nClients;
        bId = rand() % this->_m_storage->getNBooks();
        this->_m_ords.push_back(new Order(this->_m_cNames[cId], this->_m_cPhones[cId], this->_m_storage->getStorage()[bId]->getBook(), amount, i+1, this->_m_curDay + 1));
    }
}
