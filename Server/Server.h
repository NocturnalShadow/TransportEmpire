#pragma once

#include "Server/ServerBuilder.h"

#include <QObject>
#include <QString>
#include <QThread>
#include <QHostAddress>
#include <QWebSocketServer>

namespace srv {

class Router;
class ControllerSuite;
class ConnectionManager;
class ServerBuilder;

class Server : public QObject
{
    Q_OBJECT
    friend class ServerBuilder;
public:
    typedef QWebSocketServer::SslMode SecurityMode;

private:
    QString             name;
    QHostAddress        address             = QHostAddress::Any;
    quint16             port                = 8080;
    SecurityMode        securityMode        = SecurityMode::NonSecureMode;

    ConnectionManager* 	connectionManager;
    Router*				router;

    QThread*            origin;

private:
    Server();

public:
    ~Server();

public:
    static ServerBuilder build();

private:
    void setControllerSuite(ControllerSuite* suite);

public:
    void launch();
    void launchAsync();
    void terminate();

private slots:
    void onTerminate();

signals:
    void terminated();
    void launched();
    void failedToLaunch();
};

} // srv namespace

