#include "reqtablemodel.h"

#include <iostream>
ReqTableModel::ReqTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
//    this->_m_names.clear();
//    this->_m_authors.clear();
//    this->_m_editors.clear();
//    this->_m_amounts.clear();
//    this->_m_times.clear();
}

void ReqTableModel::populateData(std::deque<Request *> &reqs)
{
    this->_m_names.clear();
    this->_m_authors.clear();
    this->_m_editors.clear();
    this->_m_amounts.clear();
    this->_m_times.clear();

    this->insertRow(this->rowCount(QModelIndex()));

    for (Request * elem : reqs)
    {
        Book *book = elem->getBook();
        this->_m_names.append(QString::fromUtf8(book->getName().c_str()));
        this->_m_authors.append(QString::fromUtf8(book->getAuthor().c_str()));
        this->_m_editors.append(QString::fromUtf8(book->getEditor().c_str()));
        this->_m_amounts.append(QString::fromUtf8(std::to_string(elem->getAmount()).c_str()));
        this->_m_times.append(QString::fromUtf8(std::to_string(elem->getTime()).c_str()));
    }
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

    emit dataChanged(topLeft, bottomRight);
}

int ReqTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->_m_names.length();
}

int ReqTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant ReqTableModel::data(const QModelIndex &index, int role) const
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
        return this->_m_times[index.row()];
    return QVariant();
}

QVariant ReqTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QString("Time");
    }
    else if (role == Qt::DisplayRole && orientation == Qt::Vertical)
        return section;
    return QVariant();
}
