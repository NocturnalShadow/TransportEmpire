#pragma once

#include "Database/Entity.h"

#include "Location.h"

#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QDebug>

class City: public db::Entity
{
    PERSISTENT
private:
    QString placeID;
    QString formatedAddress;
    Location location;

public:
    City() = default;

    City(const QJsonObject& city)
        : placeID           { city["place_id"].toString() },
        formatedAddress   { city["formatted_address"].toString() },
        location          { city["loction"].toObject() }
    {
    }

    City(const QString& _placeID, const QString& _formatedAddress, const Location& _location)
        : placeID           { _placeID },
        formatedAddress   { _formatedAddress },
        location          { _location }
    {
    }

public:
    const QString&  getID()         const { return placeID; }
    const QString&  getAddress()    const { return formatedAddress; }
    const Location& getLocation()   const { return location; }

public:
    QJsonObject toJsonObject() const
    {
        QJsonObject city;
        city["place_id"]            = placeID;
        city["formatted_address"]   = formatedAddress;
        city["location"]            = location.toJsonObject();
        return city;
    }

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
