#pragma once

#include "Server/Controller.h"
#include "Database/EntityManager.h"

class UserController : public IController
{
public:
    UserController(db::EntityManager* manager);

public:
    Reply login(const Request& request);

public slots:
    void onRequestReceived(const Request& request);
};
