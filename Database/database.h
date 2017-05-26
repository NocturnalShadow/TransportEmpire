#pragma once

#include <string>
#include <memory>

#include <odb/database.hxx>

#include "entitymanager.h"

namespace db {

using namespace std;
using namespace odb;

class Database
{
private:
    string name;
    string instance;
    unique_ptr<database> db;
    unique_ptr<EntityManager> manager;

public:
    Database(const string& _name, const string& _instance = "");
    ~Database();

public:
    EntityManager* getEntityManager() { return manager.get(); }

public:
    void Connect(const string& user = "", const string& password = "");
};

}   // namespace db
