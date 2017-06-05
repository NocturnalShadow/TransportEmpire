#pragma once

#include "Specification.h"

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class Request
{
public:
    enum Type;

private:
    Type            type;
    Role            role;
    QJsonObject     data;

    bool syntaxError = false;

public:
    Request(const QString& message, Role _role = Role::CUSTOMER);
    Request(const QByteArray& message, Role _role = Role::CUSTOMER);

public:
    Type getType() const;
    Role getRole() const;

    const QJsonObject& getData() const;

    void setRole(Role _role);

    bool hasError() const;

private:
    void initialize(const QByteArray& message);
};

enum Request::Type {
    LOGIN,
    ADD_ROUTE,
    GET_ROUTE,
    GET_ROUTE_LIST
};
