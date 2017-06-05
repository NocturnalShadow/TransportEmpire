#include "Server/ConnectionManager.h"
#include "Server/ClientConnection.h"

ConnectionManager::ConnectionManager(QObject* parent)
    : QObject(parent)
{
    server = new QWebSocketServer("TransportEmpireServer",
					QWebSocketServer::NonSecureMode, this);

    connect(server, &QWebSocketServer::newConnection,
            this,   &ConnectionManager::onClientConnected);
    connect(server, &QWebSocketServer::closed,
            this,   &ConnectionManager::closed);
}

bool ConnectionManager::open(quint16 port)
{
    bool result = server->listen(QHostAddress::Any, port);
    if(result) {
        qDebug() << "Listening on port: " << port << ".";
    }
    return result;
}

void ConnectionManager::close()
{
    server->close();
    qDebug() << "Stoped listening.";
}

void ConnectionManager::onClientConnected()
{
    auto socket = server->nextPendingConnection();
    auto connection = new ClientConnection(socket, this);

    connect(connection, &ClientConnection::disconnected,
            this, &ConnectionManager::onClientDisconnected);

    connections << connection;

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
