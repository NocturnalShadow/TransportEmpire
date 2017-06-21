#include "Server/Controllers/UserController.h"
#include "Database/EntityManager.h"
#include "Utility.h"
#include "Model/Credentials.h"
#include "Model/User.h"

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
    Pointer<Credentials> cred = make<Credentials>(request.getData());
    auto query{ db::Query<User>::credentials->login ==  cred->getLogin()};
    Pointer<User> user;
    user = manager->queryOne<User>(query);
    Response response(request);
    QJsonObject data;

    if(user.data() == nullptr){
        response.setCode(Response::Code::Unauthorized);
        data["error"] = "Wrong login";
    }
    else{
        LazyPointer<Credentials> c = user->getCredentials();
        {
            db::Transaction transaction{ manager };
            c.load();
        }
        if(cred->hasPassword(c->getPassword())){
           response.setCode(Response::Code::OK);
            response.setRole(c->getRole());
            data["role"] = static_cast<int>(c->getRole());
        }
        else{
            response.setCode(Response::Code::Forbidden);
            data["error"] = "Wrong password";
        }
    }
    response.getDataRef() = data;
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
