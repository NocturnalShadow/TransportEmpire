#include "Server/Controllers/RouteController.h"

#include "Database/EntityManager.h"

namespace srv {

RouteController::RouteController(db::Database* database)
    : IController{ database }
{
}

Response RouteController::addRoute(const Request& request, db::EntityManager* manager)
{
    return Response(request);
}

Response RouteController::getRoute(const Request& request, db::EntityManager* manager)
{
    return Response(request);
}

Response RouteController::getRouteList(const Request& request, db::EntityManager* manager)
{
    return Response(request);
}

IController::RequestHandler RouteController::requestHandler(Request::Type requestType)
{
    switch(requestType)
    {
    case Request::ADD_ROUTE:
        return addRoute;
    case Request::GET_ROUTE:
        return getRoute;
    case Request::GET_ROUTE_LIST:
        return getRouteList;
    }
}

} // srv namespace
