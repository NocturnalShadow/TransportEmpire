#pragma once

#include <QObject>
#include <QWebSocket>
#include <QScopedPointer>

#include <QDebug>

#include "Specification.h"

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

