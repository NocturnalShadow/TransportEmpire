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

    Response response(request);
    response.setCode(Response::Code::OK);
    auto data = response.getDataRef();

    bool isEditing = data["edit"].toInt();

    int id = data["id"].toInt();

    data.remove("edit");
    data.remove("info");
    data.remove("polyline");
    data.remove("stops");


    Pointer<Route> route = make<Route>(data);
    if(isEditing){
       // Poiner<Route> editRoute = manager->queryOne<Route>(db::Query<Route>::id == id);
        auto editRoute = manager->load<Route>(id);
        if(editRoute.data() == nullptr){
            response.setCode(Response::Code::NotFound);
            return response;
        }
        else{
            db::Transaction transaction{ manager };
            editRoute = route;
            editRoute->update();
            transaction.commit();
        }
    }
    else{
        manager->persist(route);
    }
    //auto DBRoute = manager->queryOne<Route>(db::Query<Route>::id == id);
    auto DBRoute = manager->load<Route>(id);
    if(DBRoute.data() != route.data()){
        response.setCode(Response::Code::BadRequest);
    }
    return response;
}

Response RouteController::getRoute(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "GET_ROUTE command. " << threadId() << endl;
    Response response(request);
    response.setCode(Response::Code::OK);
    auto data = response.getDataRef();
    int id = data["id"].toInt();
    data.remove("id");
   // auto DBRoute = manager->queryOne<Route>(db::Query<Route>::id == id);
    auto DBRoute = manager->load<Route>(id);
    if(DBRoute.data() != nullptr){
        data["route"] = DBRoute->toJsonObject();
    }
    else{
        response.setCode(Response::Code::NotFound);
    }
    return response;
}

Response RouteController::getRouteList(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "GET_ROUTE_LIST command. " << threadId() << endl;
    Response response(request);
    response.setCode(Response::Code::OK);
    auto data = response.getDataRef();

    auto lazyRoutes = manager->queryLater<Route>();

    QJsonArray dataRoutes;

    if(lazyRoutes.size() != 0){
         for(auto& x: lazyRoutes){
             x.load();
            dataRoutes.push_back(QJsonValue(x->toJsonObject()));
         }
         data["routes"] = dataRoutes;
    }
    else{
        response.setCode(Response::Code::NotFound);
        data["routes"] = "There are no routes in db";
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
    default:
        return nullptr;
    }
}

} // srv namespace
