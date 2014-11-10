#ifndef SKIPLISTITEMMODEL_H
#define SKIPLISTITEMMODEL_H

#include <QAbstractListModel>
#include "skiplist.h"
class SkipListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    explicit SkipListModel(QObject *parent = 0);
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex & index) const; // return ItemIsEditable
    Q_INVOKABLE void addItem (const QString& string);
    int count() const;
signals:

void countChanged(int);
private:
    SkipList sk;
    QList<QString> nodes;
};

#endif // SKIPLISTITEMMODEL_H
