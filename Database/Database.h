#pragma once

#include <string>
#include <memory>

#include <odb/database.hxx>

namespace db {

using namespace std;
using namespace odb;

class EntityManager;
class DatabaseConnection
{
private:
    string name;
    string instance;
    unique_ptr<database> db;

public:
    DatabaseConnection(const string& _name, const string& _instance = "");
    ~DatabaseConnection();

public:
    EntityManager* manager();

public:
    void Connect(const string& user = "", const string& password = "");
};

}   // namespace db
