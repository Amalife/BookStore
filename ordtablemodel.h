#ifndef ORDTABLEMODEL_H
#define ORDTABLEMODEL_H

#include <QAbstractTableModel>
#include <string>
#include <vector>
#include "order.h"

class OrdTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit OrdTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void populateData(std::vector<Order *> &ords);

private:
    QList<QString> _m_ids;
    QList<QString> _m_cNames;
    QList<QString> _m_cPhones;
    QList<QString> _m_bNames;
    QList<QString> _m_bAuthors;
    QList<QString> _m_amounts;
    QList<QString> _m_status;
};

#endif // ORDTABLEMODEL_H
