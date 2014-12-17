#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <QObject>
#include <QVector>
class NodeItem;
typedef NodeItem* NodeItemRef;
typedef QVector<NodeItemRef> ForwardNodes;
class NodeItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString element MEMBER element )
public:
    explicit NodeItem( const QString& e ) : element( e ) {}
    ForwardNodes forward;
    QString element;
};

Q_DECLARE_METATYPE( ForwardNodes )
class SkipList : public QObject
{
    Q_OBJECT
public:
    explicit SkipList( QObject *parent = 0 );
    int size() const { return length; }
    int height() const {return list.size(); }
    bool insert ( const QString& element );
    NodeItemRef find ( const QString& element ) const;
    // return preceding nodes in @a precedings for @a element
    NodeItemRef find ( const QString& element, ForwardNodes& precedings ) const;
    bool findPrecedings ( const QString& element, ForwardNodes& precedings ) const;
    NodeItemRef remove ( const QString& element );
    QString operator()();
    void veto();
    NodeItemRef at( int index ) const;
    int indexOf ( NodeItemRef node ) const;
    int indexFor ( const QString& element ) const;
signals:
    void passBy( const ForwardNodes );
private:
    int randomize();
private:
    ForwardNodes list;
    int length;
};
#endif // SKIPLIST_H
