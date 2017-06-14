#include "Server/Controllers/UserController.h"
#include "Database/EntityManager.h"
#include "Utility.h"

#include <QTest>

namespace srv {

UserController::UserController(db::Database* database)
    : IController{ database }
{
}

Response UserController::login(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "LOGIN command. " << threadId() << endl;

    QTest::qSleep(400);         // blocks the thread

    return Response(request);
}

IController::RequestHandler UserController::requestHandler(Request::Type requestType)
{
    switch(requestType)
    {
    case Request::LOGIN:
        return login;
    default:
        return nullptr;
    }
}

} // srv namespace
