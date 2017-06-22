#include "Model/Route.h"
#include "Utility.h"

RouteInfo::RouteInfo(const QJsonObject& route)
    : totalDistance{ route["total_distance"].toDouble() }
{
}

Route::Route(const QJsonObject& route)
    : polyline{ route["polyline"].toString() },
      stops{ toVector<City>(route["stops"].toArray()) }
{
    info = make<RouteInfo>(route["info"].toObject());
    info->origin =  stops.front();
    info->destination = stops.back();
}

QJsonObject Route::toJsonObject() const
{
    QJsonObject route;
    route["id"]         = static_cast<int>(this->getId());
    route["info"]       = info->toJsonObject();
    route["polyline"]   = polyline;
    route["stops"]      = toJsonArray(stops);
    return route;
}

QJsonObject RouteInfo::toJsonObject() const
{
    QJsonObject info;
    info["origin"]          = origin->toJsonObject();
    info["destination"]     = destination->toJsonObject();
    info["total_distance"]  = totalDistance;
    return info;
}

void Route::sync(Pointer<Route> route)
{
    //routeinfo check
    Pointer<RouteInfo> routeInfo = route->info;
    if(info->totalDistance != routeInfo->totalDistance) {
        info->totalDistance = routeInfo->totalDistance;
    }
    info->origin->sync(routeInfo->origin);
    info->destination->sync(routeInfo->destination);

    //polyline check
    if(polyline != route->polyline) {
        polyline = route->polyline;
    }
    //stops check
    for(int i = 0; i < stops.size(); i++) {
        stops[i]->sync(route->stops[i]);
    }
}
