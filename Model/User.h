#pragma once

#include "Credentials.h"
#include "Specification.h"

#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

class User
{
private:
    int id;
    Role role;
    Credentials credentials;

public:
    User() = default;

public:
    int getId()     const { return id;   }
    Role getRole()  const { return role; }

    const Credentials& getCredentials() const { return credentials; }

public:
    void Debug() const
    {
        qDebug().nospace()
                << "User (id: " << id
                << ", role: "   << (int) role
                << ", login: "  << credentials.getLogin()
                << ")";
    }
};
