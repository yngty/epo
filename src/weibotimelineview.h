#ifndef WEIBOTIMELINEVIEW_H
#define WEIBOTIMELINEVIEW_H

#include <QListView>

class WeiboTimelineModel;
class WeiboTimelineView : public QListView
{
    Q_OBJECT

public:
    WeiboTimelineView(QWidget *parent = nullptr);

    void reloadData();
private:
    void initialize();
private:

    WeiboTimelineModel *model;
};

#endif // WEIBOTIMELINEVIEW_H
