#include "Server/Server.h"
#include "Server/ClientConnection.h"
#include "Server/ConnectionManager.h"
#include "Server/Router.h"
#include "Server/RouterWizard.h"

namespace srv {

Server::Server(db::Database* database, QObject* parent)
    : QObject{ parent },
      router{ new Router{ this } },
      connectionManager{
          new ConnectionManager{ name, securityMode, this }
        }
{
    RouterWizard::setUp(router, database);

    connect(connectionManager, &ConnectionManager::newConnection,
            router, &Router::registerConnection);
}

void Server::setAddress(const QHostAddress& _address) {
    address = _address;
}

void Server::setPort(quint16 _port) {
    port = _port;
}

void Server::setName(QString _name)
{
    name = _name;
}

void Server::launch() {
    isRunning = connectionManager->open(address, port);
}

void Server::stop() {
    connectionManager->close();
    emit stoped();
}

} // srv namespace
