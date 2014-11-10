#include "skiplistmodel.h"
#include <QColor>
#include <QStringList>
#include <QDebug>
SkipListModel::SkipListModel(QObject* parent) :
    QAbstractListModel(parent)
{}

int SkipListModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return sk.size();
}

QVariant SkipListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    int r = index.row ();
    NodeItemRef node = sk.at (r);
    //    qDebug () << "Index.row" << index.row ();
    if (role == ElementRole) {
        return QVariant::fromValue(node->element);
    } else if (role == IndexRole) {
        return QVariant::fromValue(r);
    } else if (role == ForwardRole) {
        QVector<int> forward;
        for (int i = 0; i < node->forward.size (); ++i) {
            forward.append (sk.indexOf (node->forward.value (i)));
        }
        return QVariant::fromValue(forward);
    }

    return QVariant();
}


Qt::ItemFlags SkipListModel::flags(const QModelIndex& index) const /* return ItemIsEditable */ {
    if (index.isValid()) {
        return QAbstractListModel::flags(index);
    }
    return Qt::NoItemFlags;
}

void SkipListModel::addItem(const QString& string)
{
    QVector<NodeItemRef> p;
    NodeItemRef node = sk.find (string, p);
    if (node) {
        return;
    }
    int index = 0;
    for (int i = 0; i < p.size (); ++i) {
        if (p.value (i)) {
            index = sk.indexOf (p.value (i)) +1;
            break;
        }
    }
    if (sk.insert (string)) {
        beginInsertRows(QModelIndex(), index, index);
        endInsertRows();
    }
    sk.veto ();
    qDebug () << sk();
}

int SkipListModel::count() const
{
    return sk.size();
}
