#pragma once

#include <QObject>
#include <QWebSocket>
#include <QHostAddress>
#include <QWebSocketServer>

namespace srv {

class ClientConnection;
class ConnectionManager : public QObject
{
	Q_OBJECT
public:
    typedef QWebSocketServer::SslMode SecurityMode;

public:
    explicit ConnectionManager(QString name, SecurityMode securityMode, QObject* parent = nullptr);

private:
    QWebSocketServer            server;
    QList<ClientConnection*>    connections;

public:
    bool open(QHostAddress address, quint16 port);
    void close();

private slots:
    void onClientConnected();
    void onClientDisconnected();

signals:
    void newConnection(ClientConnection* client);
    void closed();
};

} //srv namespace
