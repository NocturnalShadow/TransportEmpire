#pragma once

#include <QJsonObject>

#include <QDebug>

struct Location
{
public:
    double lat;
    double lng;

public:
    Location() = default;
    Location(double _lat, double _lng)
        : lat{ _lat }, lng{ _lng }
    {
    }
    Location(const QJsonObject& location)
        : lat{ location["lat"].toDouble() },
          lng{ location["lng"].toDouble() }
    {
    }

public:
    QJsonObject toJsonObject() const
    {
        QJsonObject location;
        location["lat"] = lat;
        location["lng"] = lng;
        return location;
    }

public:
    void Debug() const
    {
        qDebug().nospace()
                << "Location (lattitude: "  << lat
                << ", longitude: "          << lng
                << ")";
    }
};
