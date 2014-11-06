#include "skiplist.h"
#include <QTime>
SkipList::SkipList( QObject *parent ) :
    QObject( parent ), length( 0 )
{
    qsrand(QTime::currentTime().msecsSinceStartOfDay ());
}

int SkipList::randomize () {
    int level = 1;
    while (qrand() < (RAND_MAX>>1) && level <= list.size())
    {
        level ++;
    }
    return level;
}
bool SkipList::insert ( const QString& element ) {
    if (list.empty()) {
        NodeItemRef node = new NodeItem (element);
        node->forward.append (0);
        list.append ( node );
        return true;
    }

    // x is current check point
    NodeItemRef x = list.first ();
    // z is the node to insert
    NodeItemRef z = new NodeItem (element);
    // Case 1:
    // |-> (z = x)
    if (element == x->element) {
        delete z;
        return false;
    }
    // Case 2:
    // |->z->x
    if (element < x->element) {
        int level = randomize ();
        z->forward.fill ( 0, level );
        for (int i = 0; i < list.size (); ++i)
        {
            if (list.at (i)->element < element) {
                z->forward[i] = list.at (i);
                list[i] = z;
            }
        }
        if (level > list.size ()) {
            list.append (z);
        }
        return true;
    }

    // find a y such that:
    // x --------> y := x.f
    // x --> z --> y
    // where y.element > z.element and x.element < y.element
    int current_level = list.size ();
    for (int i = current_level - 1; i >= 0; --i) {
        if ( list.at (i)->element < element ) {
            x = list.at (i);
        }
    }
    QVector<NodeItemRef> precedings;
    int level = randomize ();
    precedings.fill (0, level);
    for (int i = x->forward.size () - 1; i >= 0; --i) {
        while (x->forward.at (i)->element >= element)
        {
            x = x->forward.at (i);
        }
        if (x->element < element) {
            precedings[i] = x;
        }
        else if (x->element == element) { // Case 3: (x = z) --> y
            delete z;
            return false;
        }
        else
        {
            throw std::bad_exception;
        }
    }
    /**
    for (int i = 0; i < level; ++i) {
        if (precedings.at (i)->element >= element) {
            throw std::bad_exception;
        }
    }
    **/
    // Case 4:
    // x --> z --> y (*|0)

    NodeItemRef y;
    Try:
    y = x->forward.at (0);
    z->forward[0] = y;
    if (y->forward.at (0)) {
        if (y->element == element) {
            delete z;
            return false;
        } else if (y->element < element) {
            x = y;
            goto Try;
        } else {
            // build link
        }
    } else {

    }
}


void SkipList::link(const QVector<NodeItemRef>& precedings, const NodeItemRef node) {
    NodeItemRef x;
    for (int i = node->forward.size () - 1; i > 0; ++i) {
        x = 0;
        if (precedings.at (i) == 0) {
            x = list.at (i);
            if (x == 0) {
                list[i] = node;
                goto Next_I;
            }
        } else {
            x = precedings.at (i);
        }
        if (x) {
            if (x->element == node->element) {
                if (x != node) {} // FIXME
            } else if (x->element > node->element) {
                list[i] = node;
                node->forward[i] = x;
                goto Next_I;
            } else {
                NodeItemRef y = x->forward[i];
                while (y &&  y->element < node->element) {
                    x = y;
                    y = x->forward[i];
                }
                x->forward[i] = node;
                node->forward[i] = y;
            }
        }
        Next_I:
    }
}
NodeItemRef SkipList::find ( const QString &element ) const {
}

