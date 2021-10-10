#include "weibotimelinemodel.h"

#include <QIcon>

#include <memory>

using namespace std;

WeiboTimelineModel::WeiboTimelineModel(QObject *parent) : QAbstractListModel(parent)
{

}

WeiboTimelineModel::WeiboTimelineModel(QList<std::shared_ptr<WeiboTimeLine>> statuses, QObject *parent)
    : QAbstractListModel(parent)
    , statuses(statuses)
{

}

QList<std::shared_ptr<WeiboTimeLine>> WeiboTimelineModel::getStatuses() const
{
    return statuses;
}

void WeiboTimelineModel::addStatus(const std::shared_ptr<WeiboTimeLine> &status)
{
    beginInsertRows(QModelIndex(), statuses.size(), statuses.size() + 1);
    statuses.append(status);
    endInsertRows();
}

int WeiboTimelineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return statuses.size();
}

QVariant WeiboTimelineModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= statuses.size() || index.row() < 0)
        return QVariant();

    const auto message = statuses[index.row()];

    if (role == Qt::DisplayRole)
        return message->text;
    if (role == DataRoles::IconNameRole)
        return QIcon::fromTheme(message->user.avatar);
    if (role == DataRoles::ContentRole)
        return message->text;

    return QVariant();
}
