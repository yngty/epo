#include "weibotimelinemodel.h"

#include <QIcon>

#include <memory>

using namespace std;

WeiboTimelineModel::WeiboTimelineModel(QObject *parent) : QAbstractListModel(parent)
{
    auto message = make_shared<WeiboTimeLine>("dde-file-manager", "yngty", "比赛结束时，他深情说道：“胜负既分，结局也已经确定了，英格兰和德国永恒的对抗在世界杯历史上继续延续下去，历史的篇章这一段已经写完。 作者：莱万少夫斯基呐 https://www.bilibili.com/read/cv9672310 出处：bilibili");
    auto message2 = make_shared<WeiboTimeLine>("computer", "timi", "西班牙球员们尽管赢球但是心情依旧比较沮丧，但是他们完全不应为此感到抱歉。因为他们已经到过很多人永远无法企及的高度。作为他们的球迷当然是得到满足还会想要更多的满足，这无可厚非，但是这种要求并不实际，因为自古打天下难，守天下更难，没有人可以永远站在顶峰。即使可以做到居安思危未雨绸缪，但是你身边全都是和你一样充满野心、充满激情和充满渴望的年轻人，他们可以把你的长处和短处放在显微镜下去研究，以你为标靶，你说守天下难不难？人生当中成功只是一时的，失败却是主旋律，但是如何面对失败却把人分成了不同的样子。有的人会被失败击垮，有的人会不断爬起来继续向前，澳大利亚队是如此，西班牙队也是如此。我想真正的成熟应该并不是追求完美，而是直面自己的缺憾，这才是生活的本质。罗曼-罗兰说过：“这个世界上只有一种真正的英雄主义，那就是认清生活的真相并且仍然热爱它。”西班牙队重头再来吧，难道向上攀爬的那条路不是比站在顶峰更令人热血澎湃吗？相信拉莫斯他们还有更多的机会，就是这样。观众朋友们，再见。");

    messages.append(message);
    messages.append(message2);
}

WeiboTimelineModel::WeiboTimelineModel(QList<std::shared_ptr<WeiboTimeLine>> messages, QObject *parent)
    : QAbstractListModel(parent)
    , messages(messages)
{

}

QList<std::shared_ptr<WeiboTimeLine>> WeiboTimelineModel::getMessages() const
{
    return messages;
}

int WeiboTimelineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return messages.size();
}

QVariant WeiboTimelineModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= messages.size() || index.row() < 0)
        return QVariant();

    const auto message = messages[index.row()];

    if (role == Qt::DisplayRole)
        return message->name;
    if (role == DataRoles::IconNameRole)
        return QIcon::fromTheme(message->icon);
    if (role == DataRoles::ContentRole)
        return message->content;

    return QVariant();
}
