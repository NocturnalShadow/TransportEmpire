#pragma once

#include "request.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

enum class ResponseCode {
	OK				= 200,
	BadRequest		= 400,
	Unauthorized	= 401,
	Forbidden		= 403,
	NotFound		= 404
};

class Reply
{
private:
    QString         command;
    ResponseCode    code;
    Role            role;

    QJsonObject     data;

public:
	Reply(const Request& request);

public:
    QJsonObject&    getDataRef();
    QString         getCommand()    const;
    Role            getRole()       const;

    void setCode(ResponseCode _code);
    void setRole(Role _role);

    QByteArray  toByteArray()        const;
    QString     toString()           const;

private:
    QJsonDocument toJsonDocument()  const;
};

