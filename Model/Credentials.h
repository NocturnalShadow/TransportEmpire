#pragma once

#include "Specification.h"
#include "Database/Entity.h"

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

class User;
class Credentials : public db::Entity
{
    PERSISTENT
private:
    QString login;
    QString password;
    Role role;
    LazyWeakPointer<User> user;

public:
    Credentials(const QJsonObject& credentials);

public:
    const QString& getLogin() const { return login; }

public:
    QJsonObject toJsonObject() const;

public:
    void Debug() const
    {
        qDebug().nospace()
                << "Credentials (login: "   << login
                << ", password: "           << password
                << ", role: "               << (int) role
                << ")";
    }
};

