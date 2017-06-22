#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Utility.h"

#include <odb/mssql/database.hxx>

namespace db {

using namespace std;
using namespace odb;

// ================================= IDatabase =================================
EntityManager* IDatabase::createManagerInstance()
{
    return new EntityManager{ db.get() };
}

// =============================== LocalDatabase ===============================
LocalDatabase::LocalDatabase(const string& _name, const string& _instance)
    : name{ _name }, instance{ _instance }
{
}

void LocalDatabase::connect(const string& user, const string& password)
{
    try {
        db = make_unique<mssql::database>(user, password, name,
                                          mssql::protocol_auto,
                                          "", instance);
        connected = true;
    } catch(std::exception& e) {
        qStdOut() << "Exception: " << e.what() << endl;
    }
}

// =============================== RemoteDatabase ===============================
RemoteDatabase::RemoteDatabase(const std::string& _name, const std::string& _host, unsigned int _port)
    : name{ _name }, host{ _host }, port{ _port }
{
}

void RemoteDatabase::connect(const string& user, const string& password)
{
    try {
        db = make_unique<mssql::database>(user, password, name, host, port);
        connected = true;
    } catch(std::exception& e) {
        qStdOut() << "Exception: " << e.what() << endl;
    }
}

} // namespace db
