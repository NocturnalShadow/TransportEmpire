#include "serverclient.hpp"
#include "routerfactory.h"

ServerClient::ServerClient(QWebSocket *soc, QObject *parent):
	QObject(parent), socket(soc)
{
	connect(socket, &QWebSocket::textMessageReceived,
			this,   &ServerClient::onClientTextMessage);
	connect(socket, &QWebSocket::binaryMessageReceived,
			this,   &ServerClient::onClientDataMessage);
	connect(socket, &QWebSocket::disconnected,
			this,   &ServerClient::onClientDisconnected);

    router = RouterFactory::create();

	connect(this,   &ServerClient::requestReceived,
            router, &Router::onRequestReceived, Qt::QueuedConnection);
	connect(router, &Router::replyReady,
            this,   &ServerClient::onReplyReady, Qt::QueuedConnection);
}

ServerClient::~ServerClient() {
	if (socket->state() != QAbstractSocket::UnconnectedState)
		socket->abort();
	delete socket;
	delete router;
}

void ServerClient::onClientTextMessage(const QString &message) {
    Request req(message, role);         // WARNING: extra copy is here
    emit requestReceived(req);          // due to the QueuedConnection
}

void ServerClient::onClientDataMessage(const QByteArray &message) {
    Request req(message, role);         // WARNING: extra copy is here
    emit requestReceived(req);          // due to the QueuedConnection
}

void ServerClient::onReplyReady(const Reply &reply) {
    if (reply.getCommand() == Command::LOGIN)
		role = reply.getRole();
	socket->sendTextMessage(reply.toString());
}

void ServerClient::onClientDisconnected() {
	emit disconnected();
}
