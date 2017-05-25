#include "Server/Controllers/UserController.h"

#include "Model/user.h"
#include "Model/credentials.h"

Reply UserController::login(const Request& request)
{
    Credentials provided{ request.getData() };

    return Reply(request);
}

void UserController::onRequestReceived(const Request& request)
{
    switch(request.getCommand())
    {
    case Command::LOGIN:
        emit replyReady(login(request));
        break;
    }
}
