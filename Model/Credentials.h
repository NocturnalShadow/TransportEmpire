#pragma once

#include "Specification.h"
#include "Database/Entity.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>


class User;
class Credentials : public db::Entity
{
    PERSISTENT
private:
    Role role;
    QString login;
    QString password;

public:
    Credentials() = default;
    Credentials(const QJsonObject& credentials);

public:
    QString getLogin()  const { return login;   }
    Role getRole()      const { return role;    }

    void setRole(Role _role) { role = _role; }

    bool hasPassword(QString _password) const {
        return password == _password;
    }

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

#include "Credentials-map.h"

