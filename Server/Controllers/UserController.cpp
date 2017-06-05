#include "Server/Controllers/UserController.h"

#include "Database/EntityManager.h"

#include "Model/User.h"
#include "Model/Credentials.h"

UserController::UserController(db::Database* database)
    : IController{ database }
{
}

Response UserController::login(const Request& request, db::EntityManager* manager)
{
    Credentials provided{ request.getData() };

    return Response(request);
}

IController::RequestHandler UserController::requestHandler(Request::Type requestType)
{
    switch(requestType)
    {
    case Request::LOGIN:
        return login;
    }
}
