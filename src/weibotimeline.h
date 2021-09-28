#ifndef WEIBOTIMELINE_H
#define WEIBOTIMELINE_H
#include <QString>

struct WeiboTimeLine
{
    QString icon;
    QString name;
    QString content;

    WeiboTimeLine() {}
    WeiboTimeLine(QString icon= "", QString name = "", QString content = "")
        :icon(icon)
        ,name(name)
        ,content(content) {}
    bool operator==(const WeiboTimeLine &other) const
    {
        return icon == other.icon && name == other.name;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const WeiboTimeLine &timeline) {
    return stream << timeline.name << timeline.content;
}

inline QDataStream &operator>>(QDataStream &stream, WeiboTimeLine &timeline)
{
    return stream >> timeline.icon >> timeline.name >> timeline.content;
}

#endif // WEIBOTIMELINE_H
