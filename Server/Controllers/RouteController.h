#pragma once

#include "Server/Controller.h"

class db::Database;
class db::EntityManager;
class RouteController : public IController
{
public:
    RouteController(db::Database* database);

private:
    static Response addRoute(const Request& request, db::EntityManager* manager);
    static Response getRoute(const Request& request, db::EntityManager* manager);
    static Response getRouteList(const Request& request, db::EntityManager* manager);

protected:
    RequestHandler requestHandler(Request::Type requestType) override;
};
