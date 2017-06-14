#include "Server/Router.h"
#include "Server/Controller.h"
#include "Server/ControllerSuite.h"
#include "Server/ClientConnection.h"

namespace srv {

Router::Router(QObject* parent)
    : QObject{ parent }
{
}

void Router::addControllerSuite(const ControllerSuite* suite)
{
    for(auto controller : suite->controllers())
    {
        connect(this, &Router::requestReceived,
                controller, &IController::onRequestReceived);
    }
}

void Router::registerConnection(ClientConnection* connection)
{
    connect(connection, &ClientConnection::requestReceived,
        [=] (const Request& request) {
            emit requestReceived(request, connection);
        });
}

} // srv namespace
