#pragma once

#include <QObject>
#include <QScopedPointer>

class Router;
class ConnectionManager;
class WebServer : public QObject
{
    Q_OBJECT
private:
    QScopedPointer<ConnectionManager>  	connectionManager;
    QScopedPointer<Router>				router;

    QHostAddress        address             = QHostAddress::Any;
    quint16             port                = 0;
    bool                isRunning           = false;

public:
    explicit WebServer(QObject* parent = nullptr);

public:
    void setAddress(const QHostAddress& _address);
    void setPort(quint16 _port);

    void launch();
    void stop();

signals:
    void stoped();
};

