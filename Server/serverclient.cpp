#include "serverclient.hpp"

ServerClient::ServerClient(QWebSocket *soc, QObject *parent):
	QObject(parent), socket(soc)
{
	connect(socket, &QWebSocket::textMessageReceived,
			this,   &ServerClient::onClientTextMessage);
	connect(socket, &QWebSocket::binaryMessageReceived,
			this,   &ServerClient::onClientDataMessage);
	connect(socket, &QWebSocket::disconnected,
			this,   &ServerClient::onClientDisconnected);

	router = new Router(this);			// NOTE: adding controller
	router->addController(new TestController);

	connect(this,   &ServerClient::requestReceived,
			router, &Router::onRequestReceived);
	connect(router, &Router::replyReady,
			this,   &ServerClient::onReplyReady);
}

ServerClient::~ServerClient(){
	if (socket->state() != QAbstractSocket::UnconnectedState)
		socket->abort();
	delete socket;
}

void ServerClient::onClientTextMessage(const QString &message) {
	Request req(message, role);
	emit requestReceived(req);
}

void ServerClient::onClientDataMessage(const QByteArray &message) {
	Request req(message, role);
	emit requestReceived(req);
}

void ServerClient::onReplyReady(const Reply &reply) {
	if (reply.getCommand() == "login")
		role = reply.getRole();
	socket->sendTextMessage(reply.toString());
}

void ServerClient::onClientDisconnected() {
	emit disconnected();
}
