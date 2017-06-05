#pragma once

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>

class ClientConnection;
class ConnectionManager : public QObject
{
	Q_OBJECT
public:
    explicit ConnectionManager(QObject* parent = nullptr);

private:
    QWebSocketServer*                   server;
    QList<ClientConnection*>            connections;

public:
    bool	open(quint16 port);
    void	close();

private slots:
    void	onClientConnected();
    void	onClientDisconnected();

signals:
    void	closed();
};

