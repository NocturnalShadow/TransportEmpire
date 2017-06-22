#pragma once

#include "Test/TestSuite.h"

#include "Model/User.h"

namespace db {
    class IDatabase;
    class EntityManager;
}

class DatabaseSuite : public QTestSuite
{
    Q_OBJECT
private:
    db::IDatabase* database;
    db::EntityManager* manager;

    Pointer<User> admin;
    Pointer<Credentials> adminCredentials;

public:
    DatabaseSuite();
    ~DatabaseSuite() {
        delete database;
    }

private slots:
    void initTestCase();
    void init();
    void cleanup();

private slots:
    void entityPersistLoadTest();
    void entityQueryTest();
    void entityQueryOneTest();
    void entityQueryLaterTest();
    void entityUpdateTest();
    void entityEraseTest();
    void transactionTest();
};
