#include "Client.h"

#include <QDebug>

namespace test {

Client::Client(QObject* parent)
    : QObject{ parent },
      responseQueue{ this, &Client::textMessageReceived }
{
    QObject::connect(&socket, &QWebSocket::connected,
            this, &Client::onConnected);
    QObject::connect(&socket, &QWebSocket::disconnected,
            this, &Client::onDisconnected);
    QObject::connect(&socket, &QWebSocket::textMessageReceived,
            this, &Client::onTextMessageReceived);
}

void Client::connect(QUrl url)
{
    socket.open(url);
}

void Client::sendMessage(QString message)
{
    socket.sendTextMessage(message);
}

QString Client::takeFirstMessage(int timeout)
{
    if(responseQueue.empty())
    {
        if(!responseQueue.wait(timeout)) {
            return "<Response timeout>";
        }
    }
    auto response = responseQueue.takeFirst();
    return response.at(0).toString();
}

void Client::onConnected()
{
}

void Client::onDisconnected()
{
    emit disconnected();
}

void Client::onTextMessageReceived(QString message)
{
    emit textMessageReceived(message);
}

} // test namespace
