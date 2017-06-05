#include "Router.h"

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

void Router::onRequestReceived(const Request& request) {
    ClientConnection* requestSender = qobject_cast<ClientConnection*>(sender());
    emit requestReceived(request, requestSender);
}
