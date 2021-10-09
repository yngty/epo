#include "weibotimelineview.h"
#include "weibotimelinemodel.h"
#include "weibotimelinedelegate.h"


WeiboTimelineView::WeiboTimelineView(QWidget *parent): QListView (parent)
{
    initialize();
}

void WeiboTimelineView::initialize()
{
    setIconSize(QSize(50, 50));

    auto model = new WeiboTimelineModel(this);
    auto delegate = new WeiboTimelineDelegate(this);

    setModel(model);
    setItemDelegate(delegate);
    setWordWrap(true);
}
