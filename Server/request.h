#ifndef REQUEST_H
#define REQUEST_H

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
	QString command;
	QJsonValue data;
	Role role = Role::CUSTOMER;

public:
	Request(const QString& _data, Role rol = Role::CUSTOMER);
	Request(const QByteArray& _data, Role rol = Role::CUSTOMER);

public:
	Role getRole()              const;
	QString getCommand()        const;
	QJsonValue getData()        const;

	void setRole(Role rol);

private:
	void parseJSON(const QJsonDocument &json);
};

#endif // REQUEST_H
