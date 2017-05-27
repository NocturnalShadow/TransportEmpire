#include "Router.h"

Router::Router(QObject* parent)
	: QObject(parent)
{
}


void Router::addController(IController* controller)
{
    controls.emplace_back(controller);
	connect(this, &Router::requestReceived,
            controller, &IController::onRequestReceived, Qt::DirectConnection);
	connect(controller, &IController::replyReady,
            this, &Router::replyReady, Qt::DirectConnection);
}

void Router::addControllers(QVector<IController*> controls)
{
	for(auto controller : controls) {
		addController(controller);
	}
}

void Router::onRequestReceived(const Request& request) {
	emit requestReceived(request);
}
