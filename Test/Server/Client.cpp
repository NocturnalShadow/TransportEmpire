#include "Test/Server/Client.h"

#include <QDebug>

namespace test {

Client::Client(const QUrl& url, QObject* parent)
    : QObject{ parent }
{
    qDebug() << "Test client started.";

    connect(&socket, &QWebSocket::connected,
            this, &Client::onConnected);
    connect(&socket, &QWebSocket::disconnected,
            this, &Client::onDisconnected);
    connect(&socket, &QWebSocket::textMessageReceived,
            this, &Client::onTextMessageReceived);

    qDebug() << "Connectiong by url: " << url;

    socket.open(url);
}

void Client::onConnected()
{
    qDebug() << "Connected.";
}

void Client::onDisconnected()
{
    qDebug() << "Disconneced.";
    emit disconnected();
}

void Client::onTextMessageReceived(QString message)
{
	qDebug() 
		<< "Message received:" << endl 
		<< message;
}

} // test namespace
