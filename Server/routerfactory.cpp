#include "router.h"
#include "routerfactory.h"

#include "Controllers/RouteController.h"
#include "Controllers/UserController.h"

Router* RouterFactory::create()
{
    Router* newRouter = new Router;
    newRouter->addController(new UserController);
    newRouter->addController(new RouteController);

    return newRouter;
}