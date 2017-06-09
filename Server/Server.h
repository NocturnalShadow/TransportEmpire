#pragma once

#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QScopedPointer>
#include <QWebSocketServer>

namespace db {
    class Database;
}

namespace srv {

class Router;
class ConnectionManager;

class Server : public QObject
{
    Q_OBJECT
    typedef QWebSocketServer::SslMode SecurityMode;
private:
    QHostAddress        address             = QHostAddress::Any;
    quint16             port                = 8080;
    QString             name                = "NamelessServer";
    SecurityMode        securityMode        = SecurityMode::NonSecureMode;

    bool                isRunning           = false;

    ConnectionManager* 	connectionManager;
    Router*				router;

public:
    explicit Server(db::Database* database, QObject* parent = nullptr);

public:
    void setAddress(const QHostAddress& _address);
    void setPort(quint16 _port);
    void setName(QString _name);

    void launch();
    void stop();

signals:
    void stoped();
};

} // srv namespace

