#include "storetablemodel.h"

StoreTableModel::StoreTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

void StoreTableModel::populateData(Instance **stor)
{
    this->_m_names.clear();
    this->_m_authors.clear();
    this->_m_editors.clear();
    this->_m_prices.clear();
    this->_m_margPrices.clear();
    this->_m_amounts.clear();

    for (int i = 0; i < 10; i++)
    {
        this->_m_names.append(QString::fromUtf8((*stor[i]).getBook()->getName().c_str()));
        this->_m_authors.append(QString::fromUtf8((*stor[i]).getBook()->getAuthor().c_str()));
        this->_m_editors.append(QString::fromUtf8((*stor[i]).getBook()->getEditor().c_str()));
        this->_m_prices.append(QString::fromUtf8(std::to_string((*stor[i]).getBook()->getPrice()).c_str()));
        this->_m_margPrices.append(QString::fromUtf8(std::to_string((*stor[i]).getBook()->getMargPrice()).c_str()));
        this->_m_amounts.append(QString::fromUtf8(std::to_string((*stor[i]).getAmount()).c_str()));
    }
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

    emit dataChanged(topLeft, bottomRight);
}

int StoreTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->_m_names.length();
}

int StoreTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant StoreTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();
    if (index.column() == 0)
        return this->_m_names[index.row()];
    else if (index.column() == 1)
        return this->_m_authors[index.row()];
    else if (index.column() == 2)
        return this->_m_editors[index.row()];
    else if (index.column() == 3)
        return this->_m_amounts[index.row()];
    else if (index.column() == 4)
        return this->_m_prices[index.row()];
    else if (index.column() == 5)
        return this->_m_margPrices[index.row()];
    return QVariant();
}

QVariant StoreTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == 0)
            return QString("Name");
        else if (section == 1)
            return QString("Author");
        else if (section == 2)
            return QString("Editor");
        else if (section == 3)
            return QString("Amount");
        else if (section == 4)
            return QString("Price");
        else if (section == 5)
            return QString("MargPrice");
    }
    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
        return section;
    return QVariant();
}
