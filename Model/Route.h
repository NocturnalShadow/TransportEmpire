#pragma once

#include "City.h"

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

class RouteInfo
{
private:
    City origin;
    City destination;
    double totalDistance;

public:
    RouteInfo(const QJsonObject& route);

public:
    double getDistance() const { return totalDistance; }

public:
    QJsonObject toJsonObject() const;
};

class Route
{
private:
    RouteInfo info;
    QString polyline;
    QVector<City> stops;

public:
    Route(const QJsonObject& route);

public:
    QJsonObject toJsonObject() const;

public:
    void Debug() const
    {
        qDebug().nospace()
                << "Route (:"
                << ", distance: "   << info.getDistance()
                << ", from: "       << stops.first().getAddress()
                << ", to: "         << stops.last().getAddress()
                <<")";
    }
};
