#include "Request.h"

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

Role Request::getRole() const {
    return role;
}

Request::Type Request::getType() const {
    return type;
}

const QJsonObject& Request::getData() const {
	return data;
}

void Request::setRole(Role _role) {
    role = _role;
}

bool Request::hasError() const {
    return syntaxError;
}

void Request::initialize(const QByteArray& message) {
    QJsonDocument document = QJsonDocument::fromJson(message);
    if(!document.isNull() && document.isObject())
    {
        QJsonObject request = document.object();
        type = (Type) request["command"].toInt();
        data = request["data"].toObject();
    } else {
        syntaxError = true;
        qDebug() << "Request parsing syntax error.";
    }

}

