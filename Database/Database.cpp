#include "Database/Database.h"
#include "Database/EntityManager.h"

#include <odb/connection.hxx>
#include <odb/mssql/database.hxx>

#include <QDebug>

namespace db {

DatabaseConnection::DatabaseConnection(const string& _name, const string& _instance)
    : name{ _name }, instance{ _instance }
{
}

DatabaseConnection::~DatabaseConnection()
{
}

EntityManager* DatabaseConnection::manager()
{
    return new EntityManager{ db.get() };
}

void DatabaseConnection::Connect(const string& user, const string& password)
{
    try {
        db = make_unique<mssql::database>(user,
                                          password,
                                          name,
                                          mssql::protocol_auto,
                                          "", instance);
    } catch(std::exception& e) {
        qDebug() << e.what();
    }
}

} // namespace db
