#pragma once

#include "Role.h"
#include "Server/Request.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMetaType>

namespace srv {

class Response
{
public:
    enum Code;

private:
    Code            code;
    Role            role;
    QJsonObject     data;

public:
    Response() = default;
    Response(const Request& request);

public:
    QJsonObject&    getDataRef();
    Role            getRole()       const;
    Code            getCode()       const;

    void setCode(Code _code);
    void setRole(Role _role);

    QByteArray  toByteArray()       const;
    QString     toString()          const;

private:
    QJsonDocument toJsonDocument()  const;
};

enum Response::Code {
    OK				= 200,
    BadRequest		= 400,
    Unauthorized	= 401,
    Forbidden		= 403,
    NotFound		= 404,
    UnknownError    = 600
};

} // srv namespace

Q_DECLARE_METATYPE(srv::Response)
