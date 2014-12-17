#include "skiplistitemmodel.h"
#include <QDebug>

SkipListListModel::SkipListListModel( QObject *parent ) :
    QAbstractListModel( parent )
{
}

Qt::ItemFlags SkipListListModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return (QAbstractListModel::flags(index)|Qt::ItemIsDragEnabled);

    return Qt::ItemIsDropEnabled;
}

void SkipListListModel::addItem( const QString &string ) {
    QVector<NodeItemRef> p;
    NodeItemRef node = sk.find( string, p );
    if ( node ) {
        return;
    }
    p.clear();
    if ( sk.insert( string ) ) {
        NodeItemRef node = sk.find( string, p );
        int idx = sk.indexOf( node );
        beginInsertRows ( QModelIndex(), idx, idx );

        endInsertRows ();
        NodeItemRef ref = p.last();
        int idy = sk.indexOf(ref);
        emit dataChanged( index(idy), index(idx) );
        emit dataChanged( index(idy), index(idx) );
        sk.veto();
    }

    // qDebug() << sk();
}

int SkipListListModel::rowCount( const QModelIndex &parent ) const {
    Q_UNUSED( parent );
    return sk.size ();
}

QModelIndex SkipListListModel::parent(const QModelIndex & index) const {
    return QModelIndex();
}

QVariant SkipListListModel::data ( const QModelIndex &index, int role ) const {
    if ( !index.isValid() ) {
        return QVariant();
    }
    int c = index.column();
    int r = index.row ();
    if ( c < 0  || r < 0) {
        return QVariant();
    }
    if (role == ElementRole) {
        return sk.at (index.row ())->element;
    }  else if (role == ForwardRole) {
        return sk.at (index.row ())->forward.size ();
    }

    return QVariant();
}

int SkipListListModel::height () {
    return sk.height ();
}
