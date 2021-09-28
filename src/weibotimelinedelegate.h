#ifndef WEIBOTIMELINEDELEGATE_H
#define WEIBOTIMELINEDELEGATE_H

#include <QStyledItemDelegate>

class WeiboTimelineView;
class WeiboTimelineDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    WeiboTimelineDelegate(QObject *parent = nullptr);
    
    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    WeiboTimelineView *par;
};

#endif // WEIBOTIMELINEDELEGATE_H
