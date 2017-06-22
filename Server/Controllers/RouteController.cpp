#include "Server/Controllers/RouteController.h"

#include "Database/EntityManager.h"

#include "Utility.h"

namespace srv {

RouteController::RouteController(db::IDatabase* database)
    : IController{ database }
{
}

Response RouteController::addRoute(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "ADD_ROUTE command. " << threadId() << endl;
    return Response(request);
}

Response RouteController::getRoute(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "GET_ROUTE command. " << threadId() << endl;
    return Response(request);
}

Response RouteController::getRouteList(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "GET_ROUTE_LIST command. " << threadId() << endl;
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
    default:
        return nullptr;
    }
}

} // srv namespace
