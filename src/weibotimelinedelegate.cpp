#include "weibotimelinedelegate.h"
#include "weibotimelineview.h"
#include "weibotimelinemodel.h"

#include <QPainter>
#include <QGuiApplication>
#include <QDebug>

#include <cmath>

WeiboTimelineDelegate::WeiboTimelineDelegate(QObject *parent) : QStyledItemDelegate (parent)
{
    par = qobject_cast<WeiboTimelineView*>(parent);
}

void WeiboTimelineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::RenderHint::Antialiasing);

    const QIcon icon = index.data(WeiboTimelineModel::IconNameRole).value<QIcon>();
    const int iconsize = par->iconSize().width();
    const int edgeMargin = 10;
    const int topMargin = 10;
    painter->drawPixmap(option.rect.x() + edgeMargin, option.rect.y() + topMargin, icon.pixmap(iconsize));

    QString name = index.data(Qt::DisplayRole).toString();

    QRect nameLabelRect = option.rect;

    const int nameLeft= iconsize + edgeMargin + edgeMargin;

    nameLabelRect.setLeft(nameLeft);
    nameLabelRect.setTop(topMargin);
    nameLabelRect.setWidth(option.rect.width() - nameLeft - edgeMargin);
    nameLabelRect.setHeight(par->fontMetrics().height());

    painter->drawText(nameLabelRect, Qt::TextWrapAnywhere, name);
    painter->drawRect(nameLabelRect);

    QString content = index.data(WeiboTimelineModel::ContentRole).toString();

    QRect contentLabelRect = nameLabelRect;
    contentLabelRect.setTop(nameLabelRect.bottom() + topMargin);
    contentLabelRect.setBottom(option.rect.bottom());

    painter->drawText(contentLabelRect, Qt::TextWrapAnywhere, content);
    painter->drawRect(contentLabelRect);

}

QSize WeiboTimelineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(400, 400);
}
