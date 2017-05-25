#pragma once

#include <odb/database.hxx>

#include <string>
#include <memory>

#include "entitymanager.h"

namespace db {

using std::string;

class Database
{
private:
    string name;
    string instance;
    std::unique_ptr<odb::database> db;
    std::unique_ptr<EntityManager> manager;

public:
    Database(const string& _name, const string& _instance = "");
    ~Database();

public:
    void Connect(const string& user = "", const string& password = "");
};

}   // namespace db
