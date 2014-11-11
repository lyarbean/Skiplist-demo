#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <QObject>
#include <QVector>
class NodeItem;
typedef NodeItem* NodeItemRef;
class NodeItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString element MEMBER element )
    Q_PROPERTY (QVector<NodeItemRef> forward MEMBER forward  NOTIFY forwardChanged)
public:
    explicit NodeItem(const QString& e) : element (e) {}

    QVector<NodeItemRef> forward;
    QString element;
signals:
    void forwardChanged();
};

Q_DECLARE_METATYPE(QVector<NodeItemRef>)
class SkipList : public QObject
{
    Q_OBJECT
public:
    explicit SkipList( QObject *parent = 0 );
    int size () const { return length; }
    bool insert ( const QString& element );
    NodeItemRef find ( const QString& element ) const;
    // return preceding nodes in @a precedings for @a element
    NodeItemRef find (const QString& element, QVector<NodeItemRef>& precedings) const;
    bool findPrecedings (const QString& element, QVector<NodeItemRef>& precedings) const;
    QString operator()();
    void veto();
    NodeItemRef at(int index) const;
    int indexOf (NodeItemRef node) const;
private:
    int randomize();
private:
    QVector<NodeItemRef> list;
    int length;
};
#endif // SKIPLIST_H
