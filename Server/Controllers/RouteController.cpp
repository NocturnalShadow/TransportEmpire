#include "Server/Controllers/RouteController.h"

#include "Database/EntityManager.h"

#include "Utility.h"
#include"Model/City.h"
#include"Model/Route.h"

namespace srv {

RouteController::RouteController(db::IDatabase* database)
    : IController{ database }
{
}

Response RouteController::addRoute(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "ADD_ROUTE command. " << threadId() << endl;

    Pointer<Route> route = make<Route>(request.getData());

    for(auto& city: route->getStops()){
        manager->persist(city);
    }
    manager->persist(route->getInfo());
    manager->persist(route);

    Response response(request);
    auto& responseData = response.getDataRef();
    responseData["id"] = (qint64) route->getId();

    return response;
}

Response RouteController::editRoute(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "EDIT_ROUTE command. " << threadId() << endl;

    Response response(request);

    auto requestData    = request.getData();
    auto id             = requestData["id"].toInt();
    auto route          = manager->load<Route>(quint64(id));

    if(route.data() == nullptr) {
        response.setCode(Response::Code::NotFound);
    } else {
        Pointer<Route> requestRoute = make<Route>(request.getData());
        route->update(requestRoute);
        route->update();
    }
    return response;
}

Response RouteController::getRoute(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "GET_ROUTE command. " << threadId() << endl;

    Response response(request);

    auto requestData  = request.getData();
    auto id     = requestData["id"].toString().toUInt();
    auto route  = manager->load<Route>(id);

    auto& responseData = response.getDataRef();

    if(route.data() != nullptr) {
        responseData["route"] = route->toJsonObject();
    } else{
        response.setCode(Response::Code::NotFound);
    }

    return response;
}

Response RouteController::getRouteList(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "GET_ROUTE_LIST command. " << threadId() << endl;

    Response response(request);

    auto& responseData  = response.getDataRef();
    auto lazyRoutes     = manager->queryLater<Route>();

    QJsonArray dataRoutes;
    if(!lazyRoutes.isEmpty())
    {
         for(auto& route : lazyRoutes)
         {
            route.load();
            dataRoutes.push_back(QJsonValue(route->toJsonObject()));
         }
         responseData["routes"] = dataRoutes;
    }
    else{
        response.setCode(Response::Code::NotFound);
    }

    return response;
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
    case Request::EDIT_ROUTE:
        return editRoute;
    default:
        return nullptr;
    }
}

} // srv namespace
