#include "Server/Controllers/UserController.h"

Reply UserController::login(const Request& request)
{
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
