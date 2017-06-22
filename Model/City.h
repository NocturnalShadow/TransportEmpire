#pragma once

#include "Database/Entity.h"

#include "Model/Location.h"

#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QDebug>

class City : public db::Entity
{
    PERSISTENT
private:
    QString placeID;
    QString formatedAddress;
    Location location;

public:
    City() = default;
    City(const QJsonObject& city);
    City(const QString& placeID, const QString& _formatedAddress, const Location& _location);

public:
    const QString&  getID()         const { return placeID; }
    const QString&  getAddress()    const { return formatedAddress; }
    const Location& getLocation()   const { return location; }

public:
    QJsonObject toJsonObject() const;

    void sync(Pointer<City> city);

public:
    void Debug() const
    {
        qDebug().nospace()
                << "City (placeID: "    << placeID
                << ", address: "        << formatedAddress
                << ", location: "       << location.lat <<  " lat, "
                                        << location.lng << " lng)";
    }
};

#include "City-map.h"

