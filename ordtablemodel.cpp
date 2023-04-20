#include "ordtablemodel.h"

OrdTableModel::OrdTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

void OrdTableModel::populateData(std::vector<Order *> &ords)
{
    this->_m_ids.clear();
    this->_m_cNames.clear();
    this->_m_cPhones.clear();
    this->_m_bNames.clear();
    this->_m_bAuthors.clear();
    this->_m_amounts.clear();
    this->_m_status.clear();

    for (Order * elem : ords)
    {
        Book *book = elem->getBook();
        std::string id = "Day_" + std::to_string(elem->getCurDay()) + ":" + std::to_string(elem->getId());
        this->_m_ids.append(QString::fromUtf8(id.c_str()));
        this->_m_cNames.append(QString::fromUtf8(elem->getName().c_str()));
        this->_m_cPhones.append(QString::fromUtf8(elem->getPhone().c_str()));
        this->_m_bNames.append(QString::fromUtf8(book->getName().c_str()));
        this->_m_bAuthors.append(QString::fromUtf8(book->getAuthor().c_str()));
        this->_m_amounts.append(QString::fromUtf8(std::to_string(elem->getAmount()).c_str()));
        int status = elem->getStatus();
        if (status == 0)
            this->_m_status.append(QString::fromUtf8("ORDERED"));
        else if (status == 1)
            this->_m_status.append(QString::fromUtf8("DELAYED"));
        else
            this->_m_status.append(QString::fromUtf8("DELIVERED"));
    }
    int n = this->_m_cNames.length();
    for (int i = 0; i < 30 - n; i++)
    {
        this->_m_ids.append(QString::fromUtf8(" "));
        this->_m_cNames.append(QString::fromUtf8(" "));
        this->_m_cPhones.append(QString::fromUtf8(" "));
        this->_m_bNames.append(QString::fromUtf8(" "));
        this->_m_bAuthors.append(QString::fromUtf8(" "));
        this->_m_amounts.append(QString::fromUtf8(" "));
        this->_m_status.append(QString::fromUtf8(" "));
    }
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

    emit dataChanged(topLeft, bottomRight);
}

int OrdTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //return this->_m_names.length();
    return 30;
}

int OrdTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7;
}

QVariant OrdTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();
    if (index.column() == 0)
        return this->_m_ids[index.row()];
    else if (index.column() == 1)
        return this->_m_cNames[index.row()];
    else if (index.column() == 2)
        return this->_m_cPhones[index.row()];
    else if (index.column() == 3)
        return this->_m_bNames[index.row()];
    else if (index.column() == 4)
        return this->_m_bAuthors[index.row()];
    else if (index.column() == 5)
        return this->_m_amounts[index.row()];
    else if (index.column() == 6)
        return this->_m_status[index.row()];
    return QVariant();
}

QVariant OrdTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == 0)
            return QString("Client ID");
        else if (section == 1)
            return QString("Client name");
        else if (section == 2)
            return QString("Client phone");
        else if (section == 3)
            return QString("Book name");
        else if (section == 4)
            return QString("Book author");
        else if (section == 5)
            return QString("Amount");
        else if (section == 6)
            return QString("Status");
    }
    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
        return section;
    return QVariant();
}
