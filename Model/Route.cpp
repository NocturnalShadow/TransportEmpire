#include "Route.h"
#include "Utility.h"

RouteInfo::RouteInfo(const QJsonObject& route)
    : //origin(route["origin"].toObject()),
      //destination(route["destination"].toObject()),
      totalDistance{ route["total_distance"].toDouble() }
{
    origin = make<City>(route["origin"].toObject());
    destination = make<City>(route["destination"].toObject());
}

QJsonObject RouteInfo::toJsonObject() const
{
    QJsonObject info;
    info["origin"] = origin->toJsonObject();
    info["destination"] = destination->toJsonObject();
    info["total_distance"] = totalDistance;
    return info;
}

Route::Route(const QJsonObject& route)
    : //info{ route["info"].toObject() },
      polyline{ route["polyline"].toString() },
      stops{ toVector<City>(route["stops"].toArray()) }
{
    info = make<RouteInfo>(route["info"].toObject());
}

QJsonObject Route::toJsonObject() const {
    QJsonObject route;
    route["id"] = static_cast<int>(this->getId());
    route["info"] = info->toJsonObject();
    route["polyline"] = polyline;
    route["stops"] = toJsonArray(stops);
    return route;
}
