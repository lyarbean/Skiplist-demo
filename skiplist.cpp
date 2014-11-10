#include "skiplist.h"
#include <QTime>
#include <QDebug>

SkipList::SkipList(QObject* parent) :
    QObject(parent), length(0)
{
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
}

int SkipList::randomize()
{
    int level = 1;
    int current_height = list.size();
    while (qrand() < (RAND_MAX >> 1) && level <= current_height) {
        level ++;
    }
    return level;
}
bool SkipList::insert(const QString& element)
{
    if (list.empty()) {
        NodeItemRef node = new NodeItem(element);
        node->forward.fill(0, 1);
        list.append(node);
        length++;
        return true;
    }
    QVector<NodeItemRef> p;
    if (!findPrecedings(element, p)) {
        qDebug() << element << "Failed";
        return false;
    }
    int level = randomize();
    NodeItemRef z = new NodeItem(element);
    z->forward.fill(0, level);
    int h = qMin(p.size(), level);
    for (int i = 0; i < h; ++i) {
        if (p.value(i)) {
            z->forward[i] = p.value(i)->forward.value(i);
            p.value(i)->forward[i] = z;
        } else {
            z->forward[i] = list.value(i);
            list[i] = z;
        }
    }
    if (level > p.size()) {
        list.append(z);
    }
    ++length;
    return true;
}


// Return false if one match
bool SkipList::findPrecedings(const QString& element, QVector<NodeItemRef>& precedings) const
{
    if (list.empty()) {
        return true;
    }
    int height = list.size();
    precedings.fill(0, height);
    NodeItemRef x = list.last();
    int h = height - 1;
    // Find one node that less than element, downwards
    while (x->element >= element && h) {
        if (x->element == element) {
            return false;
        }
        --h;
        x = list.value(h);
    }
    // Prepend
    if (h == 0) {
        if (x->element > element) {
            return true;
        }
        if (x->element == element) {
            return false;
        }
    }

    while (x && h >= 0) {
        if (x->element == element) {
            return false;
        }
        NodeItemRef y = x->forward.value(h);
        // Move forwards if possible
        while (y && y->element < element) {
            x = y;
            y = y->forward.value(h);
        }
        if (y && y->element == element) {
            return false;
        }
        // mark preceding node, when y->element > element
        if (y) { // x --> e --> y
            while (y->element > element) {
                precedings[h] = x;
                if (!h) {
                    break;
                }
                --h;
                y = x->forward.value(h);
            }
        } else {  // it stops when y is 0, try to get one not null forward, downwards
            while (h && !y) {
                precedings[h] = x;
                --h;
                y = x->forward.value(h);
            }
        }
        if (h == 0) {
            y = x->forward.value(0);
            while (y && y->element < element) {
                x = y;
                y = y->forward.value(0);
            }
            if (y && y->element == element) {
                return false;
            }
            precedings[0] = x;
            return true;
        }

    }
    return true;
}

NodeItemRef SkipList::find(const QString& element) const
{
    if (list.empty ()) {
        return 0;
    }
    QVector<NodeItemRef> p;
    return find (element, p);
}

NodeItemRef SkipList::find(const QString& element, QVector<NodeItemRef>& precedings) const
{
    if (list.empty()) {
        return 0;
    }
    int height = list.size();
    precedings.fill(0, height);
    NodeItemRef x = list.last();
    int h = height - 1;
    // Find one node that less than element, downwards
    while (x->element >= element && h) {
        if (x->element == element) {
            return x;
        }
        --h;
        x = list.value(h);
    }
    if (h == 0) {
        if (x->element > element) {
            return 0;
        }
        if (x->element == element) {
            return x;
        }
    }

    while (x && h >= 0) {
        if (x->element == element) {
            return x;
        }
        NodeItemRef y = x->forward.value(h);
        // Move forwards if possible
        while (y && y->element < element) {
            x = y;
            y = y->forward.value(h);
        }
        if (y && y->element == element) {
            return x;
        }
        // mark preceding node, when y->element > element
        if (y) { // x --> e --> y
            while (y->element > element) {
                precedings[h] = x;
                if (!h) {
                    break;
                }
                --h;
                y = x->forward.value(h);
            }
        } else {  // it stops when y is 0, try to get one not null forward, downwards
            while (h && !y) {
                precedings[h] = x;
                --h;
                y = x->forward.value(h);
            }
        }
        if (h == 0) {
            y = x->forward.value(0);
            while (y && y->element < element) {
                x = y;
                y = y->forward.value(0);
            }
            if (y && y->element == element) {
                return x;
            }
            precedings[0] = x;
            return 0;
        }

    }
    return 0;
}

QString SkipList::operator()()
{
    QString string;
    if (list.empty()) {
        string = "Empty";
        return string;
    }
    NodeItemRef x = list.value(0);
    while (x) {
        string += (x->element);
        string += (" --> ");
        x = x->forward[0];
    }
    string.append(" Nil");
    return string;
}

void SkipList::veto()
{

    if (list.empty()) {
        return;
    }
    int height = list.size();
    for (int i = 0; i < height; ++i) {
        NodeItemRef x = list.value(i);
        while (x->forward[i]) {
            if (x->element >= x->forward[i]->element) {
                qDebug() << "Error";
            }
            x = x->forward[i];
        }
    }
    qDebug() << "length:" << length;
}

// Linear search, thanks to the virtue of list
NodeItemRef SkipList::at(int row) const
{
    if (row >= length) {
        return 0;
    }
    NodeItemRef x = list.value(0);
    while (row) {
        x = x->forward.value (0);
        --row;
    }
    return x;
}

int SkipList::indexOf (NodeItemRef node) const {
    if (!node) {
        return -2;
    }
    if (list.empty ()) {
        return -1;
    }
    int index = 0;
    NodeItemRef x = list.value(0);
    while ( x && x != node ) {
        x = x->forward.value (0);
        ++index;
    }
    if (!x) {
        return -1;
    }
    return index;
}
