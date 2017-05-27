#pragma once

#include "Request.h"
#include "Specification.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class Reply
{
private:
    Command         command;
    ResponseCode    code;
    Role            role;

    QJsonObject     data;

public:
	Reply(const Request& request);

public:
    QJsonObject&    getDataRef();
    Command         getCommand()    const;
    Role            getRole()       const;

    void setCode(ResponseCode _code);
    void setRole(Role _role);

    QByteArray  toByteArray()        const;
    QString     toString()           const;

private:
    QJsonDocument toJsonDocument()  const;
};

