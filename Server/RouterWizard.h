#pragma once

#include "Server/Router.h"
#include "Server/RouterWizard.h"

#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"

namespace db {
    class Database;
}

namespace srv {

class RouterWizard
{
public:
    static void setUp(Router* router, db::Database* database)
    {
        router->addController(new UserController{ database });
        router->addController(new RouteController{ database });
    }
};

} // srv namespace
