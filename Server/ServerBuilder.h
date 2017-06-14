#pragma once

#include <QObject>
#include <QHostAddress>
#include <QWebSocketServer>

#include <memory>

namespace srv {

class Server;
class ControllerSuite;
class ServerBuilder
{
    typedef QWebSocketServer::SslMode SecurityMode;
private:
    std::unique_ptr<Server> server;

public:
    ServerBuilder();

public:
    ServerBuilder& parent(QObject* parent);
    ServerBuilder& name(QString name);
    ServerBuilder& address(QHostAddress address);
    ServerBuilder& port(quint16 _port);
    ServerBuilder& securityMode(SecurityMode securityMode);
    ServerBuilder& controllerSuite(ControllerSuite* suite);

    Server* make();
    std::unique_ptr<Server> makeUnique();
};

} // namespace srv
