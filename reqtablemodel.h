#ifndef REQTABLEMODEL_H
#define REQTABLEMODEL_H

#include <QAbstractTableModel>
#include <string>
#include <vector>
#include "request.h"

class ReqTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ReqTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void populateData(std::vector<Request *> &reqs);

private:
    QList<QString> _m_ids;
    QList<QString> _m_names;
    QList<QString> _m_authors;
    QList<QString> _m_editors;
    QList<QString> _m_amounts;
    QList<QString> _m_times;
};

#endif // REQTABLEMODEL_H
