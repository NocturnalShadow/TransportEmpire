#include "Server/Controllers/UserController.h"
#include "Database/EntityManager.h"
#include "Model/Credentials.h"
#include "Model/User.h"
#include "Utility.h"

namespace srv {

UserController::UserController(db::Database* database)
    : IController{ database }
{
}

Response UserController::login(const Request& request, db::EntityManager* manager)
{
    qStdOut() << "LOGIN command. " << threadId() << endl;

    Response response(request);
    QJsonObject& data = response.getDataRef();

    Pointer<Credentials> specifiedCredentials = make<Credentials>(request.getData());

    QJsonDocument d(request.getData());
    qStdOut() <<"cred: " << d.toJson(QJsonDocument::Compact) <<endl;

    qStdOut() << "login from site: " << specifiedCredentials->getLogin() << endl;

    Pointer<Credentials> databaseCredentials = manager->queryOne<Credentials>(
                    db::Query<Credentials>::login ==  specifiedCredentials->getLogin()
                );

    if(databaseCredentials == nullptr) {
        response.setCode(Response::Code::Unauthorized);
        data["error"] = "Wrong login.";
    } else {
        if(specifiedCredentials->hasPasswordOf(*databaseCredentials))
        {
            response.setCode(Response::Code::OK);
            response.setRole(databaseCredentials->getRole());
            data["role"] = static_cast<int>(databaseCredentials->getRole());
        } else {
            response.setCode(Response::Code::Forbidden);
            data["error"] = "Wrong password.";
        }
    }
    return response;
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
