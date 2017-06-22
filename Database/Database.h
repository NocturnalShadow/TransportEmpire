#pragma once

#include <string>
#include <memory>

#include <odb/database.hxx>

namespace db {

class EntityManager;
class IDatabase
{
protected:
    std::unique_ptr<odb::database> db;
    bool connected = false;

public:
    IDatabase() = default;
    virtual ~IDatabase() = default;

public:
    EntityManager* createManagerInstance();
    bool isConnected() const { return connected; }

    virtual void connect(const std::string& user = "", const std::string& password = "") = 0;
};

class LocalDatabase : public IDatabase
{
private:
    std::string name;
    std::string instance;

public:
    LocalDatabase(const std::string& _name, const std::string& _instance = "");

public:
    void connect(const std::string& user = "", const std::string& password = "") override;
};

class RemoteDatabase : public IDatabase
{
private:
    std::string name;
    std::string host;
    unsigned int port;

public:
    RemoteDatabase(const std::string& _name, const std::string& _host = "", unsigned int port = 1433);

public:
    void connect(const std::string& user, const std::string& password) override;
};

}   // namespace db
