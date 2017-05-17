#ifndef MODELBRIDGE_HPP
#define MODELBRIDGE_HPP

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "controller.h"

class TestController: public IController {
public:
	TestController(){}
	~TestController(){}

private:
    QJsonObject prevData;

public slots:
	void onRequestReceived(const Request& request) override {
		QString req = request.getCommand();
        if (req == "login") {
            QJsonObject d    = request.getData();
			QString login    = d["name"].toString();
			QString password = d["password"].toString();
			Reply reply(request);
			emit replyReady(reply);
		}
		else if (req == "addRoute") {
			prevData = request.getData();
			Reply reply(request);
			emit replyReady(reply);
		}
		else if (req == "getRoute") {
			Reply reply(request);
			reply.getDataRef() = prevData;
			emit replyReady(reply);
		}
		else if (req == "getRouteList") {
			Reply reply(request);
			emit replyReady(reply);
		}
	}
};

#endif // MODELBRIDGE_HPP
