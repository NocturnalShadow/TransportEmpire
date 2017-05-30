#include "Server/ClientConnection.h"
#include "Server/Request.h"
#include "Server/Reply.h"
#include "Server/Router.h"
#include "Server/RouterWizard.h"

ClientConnection::ClientConnection(QWebSocket *_socket, QObject *parent):
    QObject(parent), socket{ _socket }, router{ new Router }
{
	connect(socket, &QWebSocket::textMessageReceived,
			this,   &ClientConnection::onClientTextMessage);
	connect(socket, &QWebSocket::binaryMessageReceived,
			this,   &ClientConnection::onClientDataMessage);
	connect(socket, &QWebSocket::disconnected,
            this,   &ClientConnection::onClientDisconnected);

	connect(this,   &ClientConnection::requestReceived,
            router, &Router::onRequestReceived, Qt::QueuedConnection);
	connect(router, &Router::replyReady,
            this,   &ClientConnection::onReplyReady, Qt::QueuedConnection);

    RouterWizard::setUpControllers(router);
}

ClientConnection::~ClientConnection() {
	if (socket->state() != QAbstractSocket::UnconnectedState)
		socket->abort();
	delete socket;
	delete router;
}

void ClientConnection::onClientTextMessage(const QString &message) {
    Request req(message, role);         // WARNING: extra copy is here
    emit requestReceived(req);          // due to the QueuedConnection
}

void ClientConnection::onClientDataMessage(const QByteArray &message) {
    Request req(message, role);         // WARNING: extra copy is here
    emit requestReceived(req);          // due to the QueuedConnection
}

void ClientConnection::onReplyReady(const Reply &reply) {
    if (reply.getCommand() == Command::LOGIN)
		role = reply.getRole();
	socket->sendTextMessage(reply.toString());
}

void ClientConnection::onClientDisconnected() {
	emit disconnected();
}
