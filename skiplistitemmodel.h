#ifndef SKIPLISTITEMMODEL_H
#define SKIPLISTITEMMODEL_H

#include <QAbstractItemModel>
#include "skiplist.h"

class SkipListListModel : public QAbstractListModel
{
    Q_OBJECT
//    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    explicit SkipListListModel(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
//    Q_INVOKABLE int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    // Qt::ItemFlags flags(const QModelIndex & index) const; // return ItemIsEditable
    Q_INVOKABLE void addItem (const QString& string);
    // int count() const;
    Q_INVOKABLE int height ();
    enum ListModeRole {
        ElementRole = Qt::UserRole + 1,
        ForwardRole,
        OffsetRole
    };
    QHash<int,QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[ElementRole] = "element";
        roles[ForwardRole] = "forward";
        roles[OffsetRole] = "offset";
        return roles;
    }
signals:

//void countChanged(int);

private:
    SkipList sk;

};

#endif // SKIPLISTITEMMODEL_H
