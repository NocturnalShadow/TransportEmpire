#pragma once

#include "Specification.h"
#include "Server/Request.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class Response
{
public:
    enum Code;

private:
    Code            code;
    Role            role;
    QJsonObject     data;

public:
    Response(const Request& request);

public:
    QJsonObject&    getDataRef();
    Role            getRole()       const;

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
    NotFound		= 404
};
