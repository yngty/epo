#include "weibotimelineview.h"
#include "weibotimelinemodel.h"
#include "weibotimelinedelegate.h"
#include "networkmanager.h"
#include "weibotimeline.h"

#include <QVBoxLayout>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QVector>
#include <QDebug>

#include <memory>

WeiboTimelineView::WeiboTimelineView(QWidget *parent): QListView (parent)
{
    initialize();
}

void WeiboTimelineView::reloadData()
{
    QMap<QString, QString> params;
    params["access_token"] = NetworkManager::AccessToken;

    QByteArray response = NetworkManager::instance().get(NetworkManager::HomeTimelineUrl, params);
    if(!response.isEmpty())
    {
        QJsonParseError jsonError;
        QJsonDocument parseDoc = QJsonDocument::fromJson(response, &jsonError);
        if (!parseDoc.isNull() && (jsonError.error == QJsonParseError::NoError)) {
            /// JSON 文档为对象
            if (parseDoc.isObject()) {
                QJsonObject object = parseDoc.object();
                QJsonValue statusesValue = object.value("statuses");

                QVector<WeiboTimeLine> timelines;
                if (statusesValue.isArray()) {
                    QJsonArray statuses = statusesValue.toArray();
                    for (auto status : statuses) {

                        QJsonObject statusObject = status.toObject();
                        long long statusId = statusObject.value("id").toVariant().toLongLong();
                        QString text = statusObject.value("text").toString();

                        QJsonObject userObject = statusObject.value("user").toObject();
                        long long userId = userObject.value("id").toVariant().toLongLong();
                        QString avatar = userObject.value("avatar_large").toString();
                        QString name = userObject.value("name").toString();

                        User user(userId, avatar,name);
                        auto timeline = std::make_shared<WeiboTimeLine>(statusId, user, text);
                        model->addStatus(timeline);
                    }
                }
            }
        }
    }
}

void WeiboTimelineView::initialize()
{
    setIconSize(QSize(50, 50));

    model = new WeiboTimelineModel(this);
    auto delegate = new WeiboTimelineDelegate(this);

    setModel(model);
    setItemDelegate(delegate);
    setWordWrap(true);
}
