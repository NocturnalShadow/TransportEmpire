#pragma once

#include <string>
#include <memory>

#include <odb/database.hxx>

namespace db {

using namespace std;
using namespace odb;

class EntityManager;
class Database
{
private:
    string name;
    string instance;
    unique_ptr<database> db;

public:
    Database(const string& _name, const string& _instance = "");
    ~Database();

public:
    EntityManager* createManagerInstance();

public:
    void Connect(const string& user = "", const string& password = "");
};

}   // namespace db
