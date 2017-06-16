#include "Test/Suites/DatabaseSuite.h"
#include "Model/User.h"
#include "Utility.h"

DatabaseSuite::DatabaseSuite()
    : database{ "TransportEmpireDB" }
{
    database.connect();
    manager = database.createManagerInstance();
    manager->startSession();
}

void DatabaseSuite::DatabaseSuite::clearAllTables()
{
    manager->erase<db::Entity>(
                    db::Query<db::Entity>::id.is_not_null()
                );
}

// Tests

void DatabaseSuite::initTestCase()
{
    manager->clearTable<User>();
    manager->clearTable<Credentials>();
}

void DatabaseSuite::entityPersistLoadTest()
{
    auto admin_credentials  = make<Credentials>(Role::ADMIN, "LOGIN1", "PASSWORD1");
    auto driver_credentials = make<Credentials>(Role::DRIVER, "LOGIN2", "PASSWORD2");
    auto admin              = make<User>("Adminka", "<Unknown>", admin_credentials);
    auto driver             = make<User>("Driver 1", "<Unknown>", driver_credentials);

    manager->persist(admin_credentials);
    manager->persist(admin);
    manager->persist(driver_credentials);
    manager->persist(driver);

    auto admin_clone                = manager->load<User>(admin->getId());
    auto driver_clone               = manager->load<User>(driver->getId());
    auto admin_credentials_clone    = manager->load<Credentials>(admin_credentials->getId());
    auto driver_credentials_clone   = manager->load<Credentials>(driver_credentials->getId());

    QCOMPARE(admin_clone.data(), admin.data());
    QCOMPARE(driver_clone.data(), driver.data());
    QCOMPARE(admin_credentials_clone.data(), admin_credentials.data());
    QCOMPARE(driver_credentials_clone.data(), driver_credentials.data());
}

void DatabaseSuite::entityQueryTest()
{
    auto driver_credentials = make<Credentials>(Role::DRIVER, "LOGIN3", "PASSWORD4");
    auto driver             = make<User>("Driver 2", "<Unknown>", driver_credentials);

    manager->persist(driver_credentials);
    manager->persist(driver);

    auto drivers = manager->load<User>(db::Query<User>::firstName.like("Driver%"));

    QCOMPARE(drivers.size(), 2);

//    qSort(drivers.begin(), drivers.end(),
//    [] (auto first, auto second) {
//        return first->getFirstName() < second->getFirstName();
//    });

    QCOMPARE(drivers[0]->getFirstName(), QString{ "Driver 1" });
    QCOMPARE(drivers[1]->getFirstName(), QString{ "Driver 2" });
}


static DatabaseSuite databaseSuite;

