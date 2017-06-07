#include "Server/Server.h"
#include "Server/ClientConnection.h"
#include "Server/ConnectionManager.h"

#include "Database/Database.h"

WebServer::WebServer(QObject* parent)
    : QObject(parent)
{
}

void WebServer::setAddress(const QHostAddress& _address) {
    address = _address;
}

void WebServer::setPort(quint16 _port) {
    port = _port;
}

void WebServer::launch() {
    isRunning = connectionManager->open(address, port);
}

void WebServer::stop() {
    connectionManager->close();
    emit stoped();
}

