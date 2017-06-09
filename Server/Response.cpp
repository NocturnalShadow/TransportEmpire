#include "Server/Response.h"

namespace srv {

Response::Response(const Request& request)
    : role{ request.getRole()     },
      code{ request.hasError() ?
                Code::BadRequest : Code::OK  }
{
}

void Response::setCode(Code _code) {
    code = _code;
}

void Response::setRole(Role _role) {
    role = _role;
}

Role Response::getRole() const {
    return role;
}

Response::Code Response::getCode() const {
    return code;
}

QJsonObject& Response::getDataRef() {
	return data;
}

QString Response::toString() const {
    return toJsonDocument().toJson(QJsonDocument::Compact);
}

QByteArray Response::toByteArray() const {
    return toJsonDocument().toBinaryData();
}

QJsonDocument Response::toJsonDocument() const {
    QJsonObject reply;
    reply["code"]       = static_cast<int>(code);
    reply["data"]       = data;
    return QJsonDocument{ reply };
}

} // srv namespace
