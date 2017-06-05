#pragma once

#include "Server/Controller.h"

class db::Database;
class db::EntityManager;
class UserController : public IController
{
public:
    UserController(db::Database* database);

private:
    static Response login(const Request& request, db::EntityManager* manager);

protected:
    RequestHandler requestHandler(Request::Type requestType) override;
};
