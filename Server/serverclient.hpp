#ifndef SERVERCLIENT_HPP
#define SERVERCLIENT_HPP

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QDebug>

#include <iostream>

#include "router.h"

class ServerClient: public QObject {
	Q_OBJECT
public:
	explicit ServerClient			(QWebSocket *soc, QObject *parent = 0);
	~ServerClient					();

private:		/// <Data/>
	QWebSocket  *socket;
	Router		*router;
	Role		role = Role::CUSTOMER;

private:		/// <Engine/>

private slots:
	void	onClientTextMessage		(const QString    &message);
	void	onClientDataMessage		(const QByteArray &message);
	void    onReplyReady            (const Reply      &reply);
	void	onClientDisconnected	();

signals:
	void	requestReceived			(const Request &request);
	void	disconnected			();
};

#endif // SERVERCLIENT_HPP
