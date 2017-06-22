#pragma once

#include "Server/Request.h"
#include "Server/Response.h"

#include "Database/EntityManager.h"

#include "Utility.h"

#include <QObject>
#include <QRunnable>
#include <QScopedPointer>

namespace srv {

class Task : public QObject, public QRunnable
{
    Q_OBJECT
private:
    using RequestHandler = Response (*) (const Request&, db::EntityManager*);

private:
    QScopedPointer<Request>     request;
    RequestHandler              handler;
    db::EntityManager*          manager;

public:
    Task(const Request& _request, RequestHandler _handler, db::EntityManager* _manager)
        : request{ new Request{ _request } },
          handler{ _handler },
          manager{ _manager }
    {
    }

public:
    void run() override
    {
        manager->startSession();
        Response response;
        try {
            response = handler(*request, manager);
        } catch(std::exception& e) {
            qStdOut() << "Exception: " << e.what() << endl;
            response.setCode(Response::Code::UnknownError);
        }
        emit responseReady(response);
    }

signals:
    void responseReady(const Response& response);

};

} // srv namespace
