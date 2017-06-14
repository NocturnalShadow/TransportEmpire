#include "Server/ClientConnection.h"
#include "Server/Request.h"
#include "Server/Response.h"
#include "Utility.h"

namespace srv {

ClientConnection::ClientConnection(QWebSocket* _socket, QObject* parent)
    : QObject(parent), socket{ _socket }
{
    connect(socket.data(), &QWebSocket::textMessageReceived,
            this, &ClientConnection::onTextMessageReceived);
    connect(socket.data(), &QWebSocket::binaryMessageReceived,
            this, &ClientConnection::onBinaryMessageReceived);
    connect(socket.data(), &QWebSocket::disconnected,
            this, &ClientConnection::disconnected);
}

ClientConnection::~ClientConnection() {
    if (socket->state() != QAbstractSocket::UnconnectedState) {
		socket->abort();
    }
}

void ClientConnection::onTextMessageReceived(const QString& message) {
    qStdOut() << "Message received. " << threadId() << endl;
    emit requestReceived(Request{ message, role });
}

void ClientConnection::onBinaryMessageReceived(const QByteArray& message) {
    emit requestReceived(Request{ message, role });
}

void ClientConnection::onResponseReady(const Response& response) {
    role = response.getRole();
    socket->sendTextMessage(response.toString());
    qStdOut() << "Response ready. "  << threadId() << endl;
}

} // srv namespace
