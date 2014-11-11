#include "skiplistmodel.h"
#include <QColor>
#include <QStringList>
#include <QDebug>
SkipListModel::SkipListModel( QObject* parent ) :
    QAbstractListModel( parent )
{}

int SkipListModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent );
    return sk.size();
}

QVariant SkipListModel::data( const QModelIndex& index, int role ) const {
    if ( !index.isValid() ) {
        return QVariant();
    }
    int r = index.row();
    if ( r < 0 ) {
        return QVariant();
    }
    NodeItemRef node = nodes.at( r );
    //    qDebug () << "Index.row" << index.row ();
    if ( role == ElementRole ) {
        return QVariant::fromValue( node->element );
    } else if ( role == OffsetRole ) {
        return QVariant::fromValue( r );
    } else if ( role == ForwardRole ) {
        QVariantList forward;
        int s = node->forward.size();
        for ( int i = 0; i < s; ++i ) {
            NodeItemRef ref = node->forward.value( i );
            {
                forward.append( QVariant::fromValue( nodes.indexOf( ref ) ) );
            }
        }
        return QVariant::fromValue( forward );
    }

    return QVariant();
}

Qt::ItemFlags SkipListModel::flags( const QModelIndex& index ) const /* return ItemIsEditable */ {
    if ( index.isValid() ) {
        return QAbstractListModel::flags( index );
    }
    return Qt::NoItemFlags;
}

void SkipListModel::addItem( const QString& string )
{
    QVector<NodeItemRef> p;
    NodeItemRef node = sk.find( string, p );
    if ( node ) {
        return;
    }
    p.clear();
    if ( sk.insert( string ) ) {
        NodeItemRef node = sk.find( string, p );
        int index = sk.indexOf( node );
        // emit dataChanged for all precedings
        qDebug() << "index" << index;
        beginInsertRows( QModelIndex(), index, index );
        nodes.insert( index, node );
        endInsertRows();
    }
    sk.veto();
    qDebug() << sk();
    for ( auto ref : nodes ) {
        qDebug() << ref->element;
    }
}

int SkipListModel::count() const
{
    return sk.size();
}

