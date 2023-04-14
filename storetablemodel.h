#ifndef STORETABLEMODEL_H
#define STORETABLEMODEL_H

#include <QAbstractTableModel>
#include <map>
#include <string>
#include "book.h"

class StoreTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit StoreTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void populateData(const std::map<std::string, Book*> &stor);

private:
    QList<QString> _m_names;
    QList<QString> _m_authors;
    QList<QString> _m_editors;
    QList<QString> _m_prices;
    QList<QString> _m_margPrices;
    QList<QString> _m_amounts;
};

#endif // STORETABLEMODEL_H
