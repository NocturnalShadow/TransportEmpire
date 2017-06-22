#pragma once

#include "Database/Entity.h"
#include "Model/City.h"
#include "Utility.h"

#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QDebug>

class RouteInfo : public db::Entity
{
    PERSISTENT
    friend class Route;
private:
    Pointer<City> origin;
    Pointer<City> destination;
    double totalDistance;

public:
    RouteInfo() = default;
    RouteInfo(const QJsonObject& route);

public:
    double getDistance()            const { return totalDistance;   }
    Pointer<City> getOrigin()       const { return origin;          }
    Pointer<City> getDestination()  const { return destination;     }

public:
    QJsonObject toJsonObject() const;
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
    Route(const QJsonObject& route);

public:
    QJsonObject toJsonObject() const;

public:
    const Pointer<RouteInfo>& getInfo()         const { return info; }
    const QVector<Pointer<City>>& getStops()    const { return stops; }

    void sync(Pointer<Route> route);

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
