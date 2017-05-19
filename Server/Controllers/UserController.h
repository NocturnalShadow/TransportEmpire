#pragma once

#include "Server/controller.h"

class UserController : public IController
{
public:
    UserController() = default;

public:
    Reply login(const Request& request);

public slots:
    void onRequestReceived(const Request& request);
};
