#include "Server/ServerBuilder.h"
#include "Server/Server.h"

namespace srv {

ServerBuilder::ServerBuilder()
    : server{ new Server }
{
}

ServerBuilder& ServerBuilder::parent(QObject* parent)
{
    server->setParent(parent);
    return *this;
}

ServerBuilder& ServerBuilder::name(QString name)
{
    server->name = name;
    return *this;
}

ServerBuilder& ServerBuilder::address(QHostAddress address)
{
    server->address = address;
    return *this;
}

ServerBuilder& ServerBuilder::port(quint16 _port)
{
    server->port = _port;
    return *this;
}

ServerBuilder& ServerBuilder::securityMode(SecurityMode securityMode)
{
    server->securityMode = securityMode;
    return *this;
}

ServerBuilder& ServerBuilder::controllerSuite(ControllerSuite* suite)
{
    server->setControllerSuite(suite);
    return *this;
}

Server* ServerBuilder::make()
{
    return server.release();
}

std::unique_ptr<Server> ServerBuilder::makeUnique()
{
    return std::move(server);
}

} // namespace srv

