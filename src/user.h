#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    long long id;
    QString avatar;
    QString name;
public:
    User() = default;

    User(long long idArg, const QString &avatarArg, QString &nameArg)
        :id(idArg)
        ,avatar(avatarArg)
        ,name(nameArg) {}
};

#endif // USER_H
