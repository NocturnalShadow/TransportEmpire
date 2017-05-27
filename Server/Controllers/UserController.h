#pragma once

#include "Server/Controller.h"

class UserController : public IController
{
public:
    UserController() = default;

public:
    Reply login(const Request& request);

public slots:
    void onRequestReceived(const Request& request);
};
