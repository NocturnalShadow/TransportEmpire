#pragma once

#include "Specification.h"
#include "Database/Entity.h"
#include "Model/Credentials.h"

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

class User : public db::Entity
{
    PERSISTENT
private:
    QString firstName;
    QString lastName;
    LazyPointer<Credentials> credentials;

public:
    User() = default;

};
