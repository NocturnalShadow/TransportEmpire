#pragma once

#include "Server/Request.h"

#include <vector>
#include <memory>

#include <QObject>
#include <QVector>

namespace srv {

class IController;
class ClientConnection;

class Router : public QObject
{
	Q_OBJECT
private:
    std::vector<std::unique_ptr<IController>> controls;

public:
    explicit Router(QObject* parent = nullptr);

public:
    void addController(IController* controller);
    void addControllers(QVector<IController*> controls);

public slots:
    void registerConnection(ClientConnection* connection);

signals:
    void requestReceived(const Request& request, ClientConnection* sender);
};

} // srv namespace
