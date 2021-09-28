#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WeiboTimelineView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void initUI();
signals:

public slots:
private:
    WeiboTimelineView *timelineView ;
};

#endif // MAINWINDOW_H
