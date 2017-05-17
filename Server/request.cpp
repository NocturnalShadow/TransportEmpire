#include "request.h"

Request::Request(const QString& _data, Role rol):
	role(rol)
{
	QByteArray ba = QByteArray::fromStdString(_data.toStdString());
	QJsonDocument json = QJsonDocument::fromJson(ba);
	parseJSON(json);
}

Request::Request(const QByteArray& _data, Role rol):
	role(rol)
{
	QJsonDocument json = QJsonDocument::fromBinaryData(_data);
	parseJSON(json);
}

Role Request::getRole() const {
	return role;
}

QString Request::getCommand() const {
	return command;
}

QJsonValue Request::getData() const {
	return data;
}

void Request::setRole(Role rol) {
	role = rol;
}

void Request::parseJSON(const QJsonDocument &json) {
	QJsonObject req = json.object();
	command = req["request"].toString();
	data = req["data"];
}

