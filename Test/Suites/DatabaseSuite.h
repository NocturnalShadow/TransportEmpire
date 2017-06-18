#pragma once

#include "Test/TestSuite.h"
#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Model/User.h"

class DatabaseSuite : public QTestSuite
{
    Q_OBJECT
private:
    db::Database database;
    db::EntityManager* manager;

    Pointer<User> admin;
    Pointer<Credentials> adminCredentials;

public:
    DatabaseSuite();

private slots:
    void initTestCase();
    void init();
    void cleanup();

// Care about test order!
private slots:
    void entityPersistLoadTest();
    void entityQueryTest();
    void entityQueryOneTest();
    void entityQueryLaterTest();
    void entityUpdateTest();
    void entityEraseTest();
    void transactionTest();
};
