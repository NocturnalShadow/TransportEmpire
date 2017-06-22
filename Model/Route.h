#pragma once

#include "Database/Entity.h"
#include "City.h"
#include "Utility.h"

#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QDebug>

class RouteInfo : public db::Entity
{
    PERSISTENT
private:
    Pointer<City> origin;
    Pointer<City> destination;
    double totalDistance;

public:

    RouteInfo() = default;

    RouteInfo(const QJsonObject& route)
        : totalDistance{ route["total_distance"].toDouble() }
    {
        origin = make<City>(route["origin"].toObject());
        destination = make<City>(route["destination"].toObject());
    }

public:
    double getDistance() const { return totalDistance; }

public:
    QJsonObject toJsonObject() const
    {
        QJsonObject info;
        info["origin"] = origin->toJsonObject();
        info["destination"] = destination->toJsonObject();
        info["total_distance"] = totalDistance;
        return info;
    }
};

class Route : public db::Entity
{
    PERSISTENT
private:
    Pointer<RouteInfo> info;
    QString polyline;
    QVector<Pointer<City>> stops;

public:
    Route() = default;
    Route(const QJsonObject& route)
        : polyline{ route["polyline"].toString() },
        stops{ toVector<City>(route["stops"].toArray()) }
    {
        info = make<RouteInfo>(route["info"].toObject());
    }

public:
    QJsonObject toJsonObject() const
    {
        QJsonObject route;
        route["id"] = static_cast<int>(this->getId());
        route["info"] = info->toJsonObject();
        route["polyline"] = polyline;
        route["stops"] = toJsonArray(stops);
        return route;
    }

public:

    const Pointer<RouteInfo>& getInfo() const{return info;}
    const QVector<Pointer<City>>& getStops() const{return stops;}

    void Debug() const
        {
            qDebug().nospace()
                    << "Route ("
                    << ", distance: "   << info->getDistance()
                    << ", from: "       << stops.first()->getAddress()
                    << ", to: "         << stops.last()->getAddress()
                    <<")";
        }
};

#include "Route-map.h"
