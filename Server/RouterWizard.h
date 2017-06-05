#pragma once

#include "Server/Router.h"
#include "Server/RouterWizard.h"

#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"

class RouterWizard
{
public:
    static void setUpControllers(Router* router)
    {
        router->addController(new UserController);
        router->addController(new RouteController);
    }
};
