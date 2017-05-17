#include "reply.h"

Reply::Reply(const Request& request)
    : command   { request.getCommand()  },
      role      { request.getRole()     },
      code      { request.hasError() ?
                      ResponseCode::BadRequest :
                      ResponseCode::OK  }
{
}

void Reply::setCode(ResponseCode _code) {
    code = _code;
}

void Reply::setRole(Role _role) {
    role = _role;
}

QString Reply::getCommand() const {
	return command;
}

Role Reply::getRole() const {
    return role;
}

QJsonObject& Reply::getDataRef() {
	return data;
}

QString Reply::toString() const {
    return toJsonDocument().toJson(QJsonDocument::Compact);
}

QByteArray Reply::toByteArray() const {
    return toJsonDocument().toBinaryData();
}

QJsonDocument Reply::toJsonDocument() const {
    QJsonObject reply;
    reply["command"]    = command;
    reply["code"]       = static_cast<int>(code);
    reply["data"]       = data;
    return QJsonDocument{ reply };
}
