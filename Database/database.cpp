#include "Database/database.h"
#include "Database/entitymanager.h"

#include <odb/connection.hxx>
#include <odb/mssql/database.hxx>

#include <QDebug>

namespace db {

Database::Database(const string& _name, const string& _instance)
    : name{ _name }, instance{ _instance }
{
}

Database::~Database()
{
}

void Database::Connect(const string& user, const string& password)
{
    try {
        db      = make_unique<mssql::database>(user, password, name, mssql::protocol_auto, "", instance);
        manager = make_unique<EntityManager>(db.get());
    } catch(std::exception& e) {
        qDebug() << e.what();
    }
}

} // namespace db
