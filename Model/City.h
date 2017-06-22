#pragma once

#include "Location.h"
#include "Database/Entity.h"

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

class City:public db::Entity
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

    void update(Pointer<City> city);

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
