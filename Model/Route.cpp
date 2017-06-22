#include "Route.h"
#include "Utility.h"

RouteInfo::RouteInfo(const QJsonObject& route)
    : totalDistance{ route["total_distance"].toDouble() }
{
    //origin = make<City>(route["origin"].toObject());
    //destination = make<City>(route["destination"].toObject());
    origin = nullptr;
    destination = nullptr;
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
    : polyline{ route["polyline"].toString() },
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

void Route::update(Pointer<Route> route)
{
    //routeinfo check
    Pointer<RouteInfo> routeInfo = route->info;
    if(info->distance != routeInfo->totalDistance){
        info->distance = routeInfo->totalDistance;
    }
    info->origin->update(routeInfo->origin);
    info->destination->update(routeInfo->destination);

    //polyline check
    if(polyline != route->polyline){
        polyline = route->polyline;
    }
    //stops check
    for(int i = 0; i < stops.size(); i++){
        stops[i]->update(route->stops[i]);
    }
}
