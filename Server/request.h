#pragma once

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

enum class Role {
	CUSTOMER,
	DRIVER,
	ADMIN
};

class Request
{
private:
    QString         command;
    Role            role;

    QJsonObject     data;

    bool syntaxError = false;

public:
    Request(const QString& message, Role _role = Role::CUSTOMER);
    Request(const QByteArray& message, Role _role = Role::CUSTOMER);

public:
    const QString& getCommand()     const;
    const QJsonObject& getData()    const;

    Role getRole()                  const;
    bool hasError()                 const;

    void setRole(Role _role);

private:
    void initialize(const QByteArray& message);
};

