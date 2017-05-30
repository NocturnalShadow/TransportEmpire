#include "Server/Controllers/RouteController.h"

RouteController::RouteController(db::EntityManager* manager)
    : IController{ manager }
{
}

Reply RouteController::addRoute(const Request& request)
{
    return Reply(request);
}

Reply RouteController::getRoute(const Request& request)
{
    return Reply(request);
}

Reply RouteController::getRouteList(const Request& request)
{
    return Reply(request);
}

void RouteController::onRequestReceived(const Request& request)
{
    switch(request.getCommand())
    {
    case Command::ADD_ROUTE:
        emit replyReady(addRoute(request));
        break;
    case Command::GET_ROUTE:
        emit replyReady(getRoute(request));
        break;
    case Command::GET_ROUTE_LIST:
        emit replyReady(getRouteList(request));
        break;
    }
}
