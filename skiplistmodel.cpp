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
//    NodeItemRef node = sk.at (index.row());
//    qDebug () << "Index.row" << index.row ();
    if (role == Qt::DisplayRole) {
        return QVariant::fromValue(nodes.value (index.row ()));
    } else if (role == Qt::ForegroundRole) {
        QStringList color_names = QColor::colorNames();
        return color_names.value (index.row() % 20);
    } else if (role == Qt::DecorationRole) {
        // TODO Get indices of forwarding nodes
        return QVariant::fromValue<QVector<NodeItemRef> >(sk.at (index.row())->forward);
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
    if (sk.insert (string)) {
        QVector<NodeItemRef> p;
        NodeItemRef node = sk.find (string);
        int index = sk.indexOf (node);
        qDebug () << "Index " << index;
        beginInsertRows(QModelIndex(), index, index + 1);
        nodes.insert (index, string);
        endInsertRows();
        emit countChanged(count());
    }
}

int SkipListModel::count() const
{
    return sk.size();
}
