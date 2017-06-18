#pragma once

#include "Role.h"
#include "Database/Entity.h"
#include "Model/Credentials.h"

#include <QtCore/QDebug>
#include <QtCore/QString>

class User : public db::Entity
{
    PERSISTENT
private:
    QString firstName;
    QString lastName;
    LazyPointer<Credentials> credentials;

public:
    User() = default;
    User(QString _firstName, QString _lastName, Pointer<Credentials> _credentials)
        : firstName{ _firstName }, lastName{ _lastName }, credentials{ _credentials }
    {
    }

public:
    QString getFirstName()  const { return firstName;   }
    QString getLastName()   const { return lastName;    }
    auto getCredentials()   const { return credentials; }

    void setFirstName(QString _firstName) {
        firstName = _firstName;
    }
    void setLastName(QString _lastName) {
        lastName = _lastName;
    }

public:
    void Debug() const
    {
        qDebug().nospace()
                << "User: (firstName: " << firstName
                << ", lastName:"        << lastName
                << ")";
    }

};

#include "User-map.h"
