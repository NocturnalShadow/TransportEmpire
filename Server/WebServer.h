#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

#include <iostream>

#include "ClientConnection.h"

class WebServer: public QObject {
	Q_OBJECT
public:
	explicit WebServer				(QObject *parent = 0);

private:		/// <Data/>
    QWebSocketServer*               webServer;
    QList <ClientConnection*>       webClients;

public:			/// <Controls/>
	bool	open					(quint16 port);
	void	close					();

private:		/// <Engine/>

private slots:
	void	onClientConnected		();
	void	onClientDisconnected	();
	void	onClose					();

signals:
	void	closed					();
};

#endif /* WEBSERVER_HPP */
