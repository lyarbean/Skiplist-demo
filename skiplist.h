#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <QObject>
#include <QVector>
struct NodeItem;
typedef NodeItem* NodeItemRef;
struct NodeItem
{
    explicit NodeItem(const QString& e) : element (e) {}
    QVector<NodeItemRef> forward;
    QString element;
};

class SkipList : public QObject
{
    Q_OBJECT
public:
    explicit SkipList( QObject *parent = 0 );
    size_t size () const { return length; }
    bool insert ( const QString& element );
    NodeItemRef find ( const QString& element ) const;
    // return preceding nodes in @a precedings for @a element
    NodeItemRef find (const QString& element, QVector<NodeItemRef>& precedings) const;
    bool findPrecedings (const QString& element, QVector<NodeItemRef>& precedings) const;
    QString operator()();
    void veto();
signals:

public slots:
private:
    int randomize();
private:
    QVector<NodeItemRef> list;
    size_t length;
    // Height = Skip.size();
};
#endif // SKIPLIST_H
