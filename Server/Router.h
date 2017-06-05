#pragma once

#include "Server/Controller.h"
#include "Server/ClientConnection.h"

#include <vector>
#include <memory>

#include <QObject>
#include <QVector>

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
    void onRequestReceived(const Request& request);

signals:
    void requestReceived(const Request& request, ClientConnection* sender);
};


