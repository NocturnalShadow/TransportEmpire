#include "reply.h"

Reply::Reply(const Request& request) {
	command = request.getCommand();
	role = request.getRole();
}

void Reply::setCode(ResponseCode cod) {
	code = cod;
}

void Reply::setRole(Role rol) {
	role = rol;
}

QString Reply::getCommand() const {
	return command;
}

QJsonValue& Reply::getDataRef() {
	return data;
}

Role Reply::getRole() const {
	return role;
}

QString Reply::toString() const {
	QJsonDocument json(createJsonObject());
	return json.toJson(QJsonDocument::Compact);
}

QByteArray Reply::toByteArray() const {
	QJsonDocument json(createJsonObject());
	return json.toBinaryData();
}

QJsonObject Reply::createJsonObject() const {
	QJsonObject rep;
	rep["response"] = command;
	rep["code"] = int(code);
	rep["data"] = data;
	return rep;
}
