#include "Route.h"
#include "Utility.h"

RouteInfo::RouteInfo(const QJsonObject& route)
    : origin{ route["origin"].toObject() },
      destination{ route["destination"].toObject() },
      totalDistance{ route["total_distance"].toDouble() }
{
}

QJsonObject RouteInfo::toJsonObject() const
{
    QJsonObject info;
    info["origin"] = origin.toJsonObject();
    info["destination"] = destination.toJsonObject();
    info["total_distance"] = totalDistance;
    return info;
}

Route::Route(const QJsonObject& route)
    : info{ route["info"].toObject() },
      polyline{ route["polyline"].toString() },
      stops{ toVector<City>(route["stops"].toArray()) }
{
}

QJsonObject Route::toJsonObject() const {
    QJsonObject route;
    route["info"] = info.toJsonObject();
    route["polyline"] = polyline;
    route["stops"] = toJsonArray(stops);
    return route;
}
