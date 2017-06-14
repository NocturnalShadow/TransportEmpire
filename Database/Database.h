#pragma once

#include <string>
#include <memory>

#include <odb/database.hxx>

namespace db {

class EntityManager;
class Database
{
private:
    std::string name;
    std::string instance;
    std::unique_ptr<odb::database> db;

public:
    Database(const std::string& _name, const std::string& _instance = "");
    ~Database();

public:
    EntityManager* createManagerInstance();

public:
    void connect(const std::string& user = "", const std::string& password = "");
};

}   // namespace db
