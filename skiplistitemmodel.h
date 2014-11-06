#ifndef SKIPLISTITEMMODEL_H
#define SKIPLISTITEMMODEL_H

#include <QAbstractItemModel>

class SkipListItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SkipListItemModel(QObject *parent = 0);

signals:

public slots:

};

#endif // SKIPLISTITEMMODEL_H
