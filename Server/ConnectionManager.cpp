#include "Server/ConnectionManager.h"
#include "Server/ClientConnection.h"

namespace srv {

ConnectionManager::ConnectionManager(QString name, SecurityMode securityMode, QObject* parent)
    : QObject{ parent }, server{ name, securityMode, this }
{
    connect(&server, &QWebSocketServer::newConnection,
            this, &ConnectionManager::onClientConnected);
    connect(&server, &QWebSocketServer::closed,
            this, &ConnectionManager::closed);
}

bool ConnectionManager::open(QHostAddress address, quint16 port)
{
    bool result = server.listen(address, port);
    if(result) {
        qDebug() << "Listening by address:" << address
                 << "on port: " << port << ".";
    }
    return result;
}

void ConnectionManager::close()
{
    server.close();
    qDebug() << "Stoped listening.";
}

void ConnectionManager::onClientConnected()
{
    auto socket = server.nextPendingConnection();
    auto connection = new ClientConnection(socket, this);

    connect(connection, &ClientConnection::disconnected,
            this, &ConnectionManager::onClientDisconnected);

    connections << connection;

    emit newConnection(connection);

    qDebug() << "Client connected.";
}

void ConnectionManager::onClientDisconnected()
{
    auto connection = qobject_cast<ClientConnection*>(sender());
    if(connection != nullptr)
    {
        connections.removeAll(connection);
        connection->deleteLater();

        qDebug() << "Client disconnected.";
    }
}

} // srv namespace
