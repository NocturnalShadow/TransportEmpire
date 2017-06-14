#pragma once

#include "Server/Request.h"
#include "Server/ControllerSuite.h"

#include <QObject>

namespace srv {

class IController;
class ControllerSuite;
class ClientConnection;

class Router : public QObject
{
	Q_OBJECT
public:
    explicit Router(QObject* parent = nullptr);

public:
    void addControllerSuite(const ControllerSuite* suite);

public slots:
    void registerConnection(ClientConnection* connection);

signals:
    void requestReceived(const Request& request, ClientConnection* sender);
};

} // srv namespace
