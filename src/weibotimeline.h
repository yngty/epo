#ifndef WEIBOTIMELINE_H
#define WEIBOTIMELINE_H

#include "user.h"



class WeiboTimeLine
{

public:
    WeiboTimeLine() = default;
    WeiboTimeLine(long long idArg, const User userArg, const QString textArg = "")
        :id(idArg)
        ,user(userArg)
        ,text(textArg) {}

    bool operator==(const WeiboTimeLine &other) const
    {
        return id == other.id;
    }
public:
    long long id;
    User user;
    QString text;
};


#endif // WEIBOTIMELINE_H
