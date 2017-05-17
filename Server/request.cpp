#include "request.h"

#include <QDebug>

Request::Request(const QString& message, Role _role)
    : role{ _role }
{
    initialize(message.toUtf8());
}

Request::Request(const QByteArray& message, Role _role)
    : role{ _role }
{
    initialize(message);
}

const QString& Request::getCommand() const {
	return command;
}

const QJsonObject& Request::getData() const {
	return data;
}

Role Request::getRole() const {
    return role;
}

bool Request::hasError() const {
    return syntaxError;
}


void Request::setRole(Role _role) {
    role = _role;
}

void Request::initialize(const QByteArray& message) {
    QJsonDocument document = QJsonDocument::fromJson(message);
    if(!document.isNull() && document.isObject())
    {
        QJsonObject request = document.object();
        command = request["command"].toString();
        data    = request["data"].toObject();
    } else {
        syntaxError = true;
        qDebug() << "Request parsing syntax error.";
    }

}

