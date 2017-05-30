#pragma once

#include "Server/Reply.h"
#include "Server/Request.h"
#include "Database/EntityManager.h"

#include <QObject>

class IController : public QObject
{
	Q_OBJECT
    Q_DISABLE_COPY(IController)
private:
    db::EntityManager* manger;

public:
    IController(db::EntityManager* _manager)
        : manger{ _manager }
    {
    }
    virtual ~IController() = default;

public slots:
	virtual void onRequestReceived(const Request& request) = 0;

signals:
	void replyReady(const Reply& reply);
};
