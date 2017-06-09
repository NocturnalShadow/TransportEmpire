#pragma once

#include "Role.h"

#include <QObject>
#include <QWebSocket>
#include <QScopedPointer>

namespace srv {

class Request;
class Response;
class ClientConnection : public QObject
{
	Q_OBJECT
    friend class IController;
public:
    explicit ClientConnection(QWebSocket* _socket, QObject* parent = nullptr);
    ~ClientConnection();

private:
    QScopedPointer<QWebSocket> socket;
    Role role = Role::CUSTOMER;

private slots:
    void onTextMessageReceived(const QString& message);
    void onBinaryMessageReceived(const QByteArray& message);
    void onResponseReady(const Response& response);

signals:
    void requestReceived(const Request &request);
    void disconnected();
};

} // srv namespace
