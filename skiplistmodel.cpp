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
    NodeItemRef node = sk.at( r );
    Q_ASSERT( node );
    if ( role == ElementRole ) {
        return QVariant::fromValue( node->element );
    } else if ( role == OffsetRole ) {
        return QVariant::fromValue( r );
    } else if ( role == ForwardRole ) {
        QVariantList forward;
        int s = node->forward.size();
        for ( int i = 0; i < s; ++i ) {
            NodeItemRef ref = node->forward.value( i );
            forward.append( QVariant::fromValue( sk.indexOf( ref ) ) );
        }
        return QVariant::fromValue( forward );
    }

    return QVariant();
}

Qt::ItemFlags SkipListModel::flags( const QModelIndex& index ) const /* return ItemIsEditable */ {
    if ( index.isValid() ) {
        return QAbstractListModel::flags( index ) | Qt::ItemIsEditable;
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
    int node_index = sk.indexFor( string );

    beginInsertRows( QModelIndex(), node_index, node_index );
    sk.insert( string );
    endInsertRows();

//    if ( sk.insert( string ) ) {

//       // NodeItemRef node = sk.find( string, p );

//        // emit dataChanged for all precedings
//        for ( auto ref : p ) {
//            int offset = sk.indexOf( ref );
//            if ( offset >= 0 && offset + 1 != node_index) {
////                QVariantList forward;
////                int s = ref->forward.size();
////                for ( int i = 1; i < s; ++i ) {
////                    NodeItemRef f = ref->forward.value( i );
////                    forward.append( QVariant::fromValue( sk.indexOf( f ) ) );
////                }
                beginResetModel();
                endResetModel();
//            }
//        }
//    }

    sk.veto();
    qDebug() << sk();
}

int SkipListModel::count() const {
    return sk.size();
}

