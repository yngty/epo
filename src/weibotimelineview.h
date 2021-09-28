#ifndef WEIBOTIMELINEVIEW_H
#define WEIBOTIMELINEVIEW_H

#include <QListView>

class WeiboTimelineView : public QListView
{
    Q_OBJECT

public:
    WeiboTimelineView(QWidget *parent = nullptr);
private:
    void initialize();
};

#endif // WEIBOTIMELINEVIEW_H
