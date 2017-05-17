#ifndef REPLY_H
#define REPLY_H

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
	QString command;
	ResponseCode code = ResponseCode::OK;
	QJsonValue data = QJsonObject();
	Role role = Role::CUSTOMER;

public:
	Reply() = default;
	Reply(const Request& request);

public:
	void setCode(ResponseCode cod);
	void setRole(Role rol);
	QString getCommand() const;
	QJsonValue &getDataRef();
	Role getRole() const;

	QString toString() const;
	QByteArray toByteArray() const;

private:
	QJsonObject createJsonObject() const;
};

#endif // REPLY_H
