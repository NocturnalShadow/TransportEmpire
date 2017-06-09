#include "Server/Router.h"
#include "Server/Controller.h"
#include "Server/ClientConnection.h"

namespace srv {

Router::Router(QObject* parent)
	: QObject(parent)
{
}


void Router::addController(IController* controller)
{
    controls.emplace_back(controller);
	connect(this, &Router::requestReceived,
            controller, &IController::onRequestReceived);
}

void Router::addControllers(QVector<IController*> _controls)
{
    for(auto controller : _controls) {
		addController(controller);
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
