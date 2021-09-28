#ifndef WEIBOTIMELINEMODEL_H
#define WEIBOTIMELINEMODEL_H

#include <QAbstractListModel>
#include "weibotimeline.h"

#include <memory>

class WeiboTimelineModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRoles
    {
        IconNameRole = Qt::UserRole + 1,    // 头像
        ContentRole = Qt::UserRole + 2,    // 内容
    };
    explicit WeiboTimelineModel(QObject *parent = nullptr);
    explicit WeiboTimelineModel(QList<std::shared_ptr<WeiboTimeLine>> messages, QObject *parent = nullptr);

    QList<std::shared_ptr<WeiboTimeLine>> getMessages() const;
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private:
    QList<std::shared_ptr<WeiboTimeLine>> messages;
};
#endif // WEIBOTIMELINEMODEL_H
