#pragma once

#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Server/ClientConnection.h"
#include "Server/Response.h"
#include "Server/Request.h"
#include "Server/Task.h"

#include <QObject>
#include <QThreadPool>

namespace srv {

class IController : public QObject
{
	Q_OBJECT
protected:
    using RequestHandler = Response (*) (const Request&, db::EntityManager* manager);

private:
    QThreadPool*    pool = QThreadPool::globalInstance();
    db::Database*   database;

public:
    IController(db::Database* _database)
        : database{ _database }
    {
    }
    virtual ~IController() = default;

protected:
    virtual RequestHandler requestHandler(Request::Type requestType) = 0;

public slots:
    void onRequestReceived(const Request& request, ClientConnection* sender)
    {
        RequestHandler handler = requestHandler(request.getType());
        if(handler != nullptr)
        {
            Task* task = new Task{ request, handler, database->createManagerInstance() };
            connect(task, &Task::responseReady,
                    sender, &ClientConnection::onResponseReady,
                    Qt::QueuedConnection);
            pool->start(task);
        }
    }
};

} // srv namespace
