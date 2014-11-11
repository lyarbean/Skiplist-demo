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
//    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

signals:

void countChanged(int);
private:
    SkipList sk;
    QList<NodeItemRef> nodes;
};

#endif // SKIPLISTITEMMODEL_H
