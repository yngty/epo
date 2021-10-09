#include "weibotimelinedelegate.h"
#include "weibotimelineview.h"
#include "weibotimelinemodel.h"

#include <QPainter>
#include <QTextLayout>
#include <QGuiApplication>
#include <QDebug>
#include <QMap>

#include <cmath>

QMap<int, int> heights;
WeiboTimelineDelegate::WeiboTimelineDelegate(QObject *parent) : QStyledItemDelegate (parent)
{
    par = qobject_cast<WeiboTimelineView*>(parent);
}

void WeiboTimelineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::RenderHint::Antialiasing);

    const int edgeMargin = 10;
    const int iconWidth = par->iconSize().width();
    const int rectWidth = option.rect.width();

    const QIcon icon = index.data(WeiboTimelineModel::IconNameRole).value<QIcon>();
    const QRect iconRect(edgeMargin,option.rect.top() + edgeMargin, iconWidth, iconWidth);
    painter->drawPixmap(iconRect, icon.pixmap(iconRect.size()));

    const QString name = index.data(Qt::DisplayRole).toString();
    const int nameLabelLeft = edgeMargin * 2 + iconWidth;
    QRect nameLabelRect(nameLabelLeft, option.rect.top() +  edgeMargin, rectWidth - nameLabelLeft - edgeMargin, option.fontMetrics.height());

    painter->drawText(nameLabelRect, Qt::TextWrapAnywhere, name);

    const QString content = index.data(WeiboTimelineModel::ContentRole).toString();
    qreal height = 0;
    if (heights.contains(index.row())) {
        height = heights[index.row()];
    } else {
        QTextLayout textLayout(content);
        textLayout.beginLayout();
        while (true) {
            QTextLine line = textLayout.createLine();
            if (!line.isValid())
                break;

            line.setLineWidth(option.rect.width() - edgeMargin * 2 - iconWidth);
            line.setPosition(QPointF(0, height));
            height += line.height();

        }
        textLayout.endLayout();
        heights.insert(index.row(), static_cast<int>(height));
    }


    QRect contentLabelRect = nameLabelRect;
    contentLabelRect.setTop(nameLabelRect.bottom());
    contentLabelRect.setHeight(static_cast<int>(height));
    painter->drawText(contentLabelRect, Qt::TextWrapAnywhere, content);
}

QSize WeiboTimelineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    const int edgeMargin = 10;
    const int iconWidth = par->iconSize().width();

    const QString content = index.data(WeiboTimelineModel::ContentRole).toString();
    qreal height = 0;
    if (heights.contains(index.row())) {
        height = heights[index.row()];
    } else {
        QTextLayout textLayout(content);
        textLayout.beginLayout();
        while (true) {
            QTextLine line = textLayout.createLine();
            if (!line.isValid())
                break;

            line.setLineWidth(option.rect.width() - edgeMargin * 2 - iconWidth);
            line.setPosition(QPointF(0, height));
            height += line.height();

        }
        textLayout.endLayout();
        heights.insert(index.row(), static_cast<int>(height));
    }

    QSize size(option.rect.width(), edgeMargin + option.fontMetrics.height() + static_cast<int>(height));

    return size;
}
