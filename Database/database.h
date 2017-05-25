#pragma once

#include <odb/database.hxx>
#include <odb/connection.hxx>
#include <odb/mssql/database.hxx>

#include <QString>
#include <QSharedPointer>

class Database
{
private:
	QString name;
	QSharedPointer<odb::database> db;

public:
	Database(const QString& _name);

public:
	void Create();
};