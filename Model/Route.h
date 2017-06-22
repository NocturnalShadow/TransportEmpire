#pragma once

#include "City.h"
#include "Database/Entity.h"

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

class RouteInfo : public db::Entity
{
    PERSISTENT
private:
    Pointer<City> origin;
    Pointer<City> destination;
    double totalDistance;

public:
    RouteInfo(const QJsonObject& route);

public:
    double getDistance() const { return totalDistance; }

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
    Route(const QJsonObject& route);

public:
    QJsonObject toJsonObject() const;

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
