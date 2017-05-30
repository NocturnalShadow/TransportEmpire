#pragma once

#include "Server/Router.h"
#include "Server/RouterWizard.h"

#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"

#include "Database/EntityManager.h"

class RouterWizard
{
public:
    static void setUpControllers(Router* router, db::EntityManager* manager = nullptr)
    {
        router->addController(new UserController{ manager });
        router->addController(new RouteController{ manager });
    }
};
