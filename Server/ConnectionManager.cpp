#include "Server/ConnectionManager.h"
#include "Server/ClientConnection.h"
#include "Server/Request.h"
#include "Server/Response.h"

#include "Utility.h"

#include <QMetaType>

namespace srv {

ConnectionManager::ConnectionManager(QString name, SecurityMode securityMode, QObject* parent)
    : QObject{ parent }, server{ name, securityMode, this }
{
    qRegisterMetaType<Request>("Request");
    qRegisterMetaType<Response>("Response");

    connect(&server, &QWebSocketServer::newConnection,
            this, &ConnectionManager::onClientConnected);
    connect(&server, &QWebSocketServer::closed,
            this, &ConnectionManager::closed);
}

bool ConnectionManager::open(QHostAddress address, quint16 port)
{
    bool result = server.listen(address, port);
    if(result) {
        qStdOut()
                << "Listening by address: " << address.toString()
                << " on port: " << port << ". " << threadId()
                << endl;
    }
    return result;
}

void ConnectionManager::close()
{
    server.close();
    qStdOut() << "Stoped listening. " << threadId();
}

void ConnectionManager::onClientConnected()
{
    auto socket = server.nextPendingConnection();
    auto connection = new ClientConnection(socket, this);

    connect(connection, &ClientConnection::disconnected,
            this, &ConnectionManager::onClientDisconnected);

    connections << connection;

    emit newConnection(connection);

    qStdOut() << "Client connected." << threadId() << endl;
}

void ConnectionManager::onClientDisconnected()
{
    auto connection = qobject_cast<ClientConnection*>(sender());
    if(connection != nullptr)
    {
        connections.removeAll(connection);
        connection->deleteLater();

        qStdOut() << "Client disconnected." << threadId() << endl;
    }
}

} // srv namespace
