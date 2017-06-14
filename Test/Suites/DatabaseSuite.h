#pragma once

#include "Test/TestSuite.h"
#include "Database/Database.h"
#include "Database/EntityManager.h"


class DatabaseSuite : public QTestSuite
{
    Q_OBJECT
private:
    db::Database database;
    db::EntityManager* manager;

public:
    DatabaseSuite();

private slots:
    void entityManagerTest();
};
