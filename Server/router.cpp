#include "router.h"

Router::Router(QObject *parent)
    : QObject(parent)
{
}

void Router::addController(IController* controller)
{
    controls.append(controller);
    connect(this, &Router::requestReceived,
            controller, &IController::onRequestReceived);
    connect(controller, &IController::replyReady,
            this, &Router::replyReady);
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

Router* Router::createDefault() {
    return nullptr;
}
