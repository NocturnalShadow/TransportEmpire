#include "ClientConnection.h"
#include "RouterFactory.h"

ClientConnection::ClientConnection(QWebSocket *soc, QObject *parent):
	QObject(parent), socket(soc)
{
	connect(socket, &QWebSocket::textMessageReceived,
			this,   &ClientConnection::onClientTextMessage);
	connect(socket, &QWebSocket::binaryMessageReceived,
			this,   &ClientConnection::onClientDataMessage);
	connect(socket, &QWebSocket::disconnected,
			this,   &ClientConnection::onClientDisconnected);

    router = RouterFactory::create();

	connect(this,   &ClientConnection::requestReceived,
            router, &Router::onRequestReceived, Qt::QueuedConnection);
	connect(router, &Router::replyReady,
            this,   &ClientConnection::onReplyReady, Qt::QueuedConnection);
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
