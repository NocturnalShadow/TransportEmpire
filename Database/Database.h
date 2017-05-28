#pragma once

#include <string>
#include <memory>

#include <odb/database.hxx>

#include "Database/EntityManager.h"

namespace db {

using namespace std;
using namespace odb;

class DatabaseConnection
{
private:
    string name;
    string instance;
    unique_ptr<database> db;
    unique_ptr<EntityManager> manager;

public:
    DatabaseConnection(const string& _name, const string& _instance = "");
    ~DatabaseConnection();

public:
    EntityManager* getEntityManager() { return manager.get(); }

public:
    void Connect(const string& user = "", const string& password = "");
};

}   // namespace db
