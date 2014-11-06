#ifndef SKIPLISTITEMMODEL_H
#define SKIPLISTITEMMODEL_H

#include <QAbstractItemModel>

class SkipListItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SkipListItemModel(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex());
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const; // return ItemIsEditable
signals:

public slots:

};

#endif // SKIPLISTITEMMODEL_H
