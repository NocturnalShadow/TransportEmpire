#pragma once

#include "reply.h"
#include "request.h"

#include <QObject>

class IController : public QObject
{
	Q_OBJECT
public:
    virtual ~IController()
    {
    }

public slots:
	virtual void onRequestReceived(const Request& request) = 0;

signals:
	void replyReady(const Reply& reply);
};
