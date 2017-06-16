#pragma once

#include "Test/TestSuite.h"
#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Utility.h"

#include <QString>

class DatabaseSuite : public QTestSuite
{
    Q_OBJECT
private:
    db::Database database;
    db::EntityManager* manager;

public:
    DatabaseSuite();

private:
void DatabaseSuite::clearAllTables();

// Care about test order!
private slots:
void initTestCase();
void entityPersistLoadTest();
void entityQueryTest();
//    TODO:
//    void entityUpdateTest();
//    void entityEraseTest();
//    void cleanupTestCase();
};
