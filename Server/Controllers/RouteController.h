#pragma once

#include "Server/Controller.h"
#include "Database/EntityManager.h"

class RouteController : public IController
{
public:
    RouteController(db::EntityManager* manager);

private:
    Reply addRoute(const Request& request);
    Reply getRoute(const Request& request);
    Reply getRouteList(const Request& request);

public slots:
    void onRequestReceived(const Request& request);

};
