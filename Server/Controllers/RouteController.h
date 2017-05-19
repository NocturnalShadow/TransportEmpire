#pragma once

#include "Server/controller.h"

class RouteController : public IController
{
public:
    RouteController() = default;

private:
    Reply addRoute(const Request& request);
    Reply getRoute(const Request& request);
    Reply getRouteList(const Request& request);

public slots:
    void onRequestReceived(const Request& request);

};
