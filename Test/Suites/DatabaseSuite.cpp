#include "Test/Suites/DatabaseSuite.h"

#include "Utility.h"

DatabaseSuite::DatabaseSuite()
    : database{ "TransportEmpireDB" }
{
    database.connect();
    manager = database.createManagerInstance();
    manager->startSession();
}

// Tests

void DatabaseSuite::initTestCase()
{
    manager->erase<db::Entity>();
}

void DatabaseSuite::entityPersistLoadTest()
{
    auto adminClone               = manager->load<User>(admin->getId());
    auto adminCredentialsClone    = manager->load<Credentials>(adminCredentials->getId());

    QCOMPARE(adminClone.data(), admin.data());
    QCOMPARE(adminCredentialsClone.data(), adminCredentials.data());
}

void DatabaseSuite::entityQueryTest()
{
    auto drivers = manager->query<User>(db::Query<User>::firstName.like("Driver%"));

    QCOMPARE(drivers.size(), 2);

    // return order is not defined
    qSort(drivers.begin(), drivers.end(),
    [] (auto first, auto second) {
        return first->getFirstName() < second->getFirstName();
    });

    QCOMPARE(drivers[0]->getFirstName(), QString{ "Driver 1" });
    QCOMPARE(drivers[1]->getFirstName(), QString{ "Driver 2" });
}

void DatabaseSuite::entityQueryOneTest()
{
    admin = manager->queryOne<User>(db::Query<User>::credentials->role == Role::ADMIN);
    QCOMPARE(admin->getFirstName(), QString{ "Adminka" });
}

void DatabaseSuite::entityQueryLaterTest()
{
    auto lazyDrivers = manager->queryLater<User>(db::Query<User>::firstName.like("Driver%"));

    QCOMPARE(lazyDrivers.size(), 2);

    for(auto& driver : lazyDrivers) {
        driver.load();
    }

    // return order is not defined
    qSort(lazyDrivers.begin(), lazyDrivers.end(),
    [] (auto first, auto second) {
        return first->getFirstName() < second->getFirstName();
    });

    QCOMPARE(lazyDrivers[0]->getFirstName(), QString{ "Driver 1" });
    QCOMPARE(lazyDrivers[1]->getFirstName(), QString{ "Driver 2" });
}

void DatabaseSuite::entityUpdateTest()
{
    {
        auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
        driver->setLastName("Erickson");
        driver->update();
    }

     auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
     QCOMPARE(driver->getLastName(), QString{ "Erickson" });
}

void DatabaseSuite::entityEraseTest()
{
    {
        auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
        driver->erase();
    }

    auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
    QCOMPARE(driver.data(), nullptr);
}

void DatabaseSuite::transactionTest()
{
    auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
    {
        auto transaction = manager->transaction();
        driver->setLastName("Erickson");
        driver->update();
    }

    manager->reload(driver);
//    driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
    QCOMPARE(driver->getLastName(), QString{ "<Unknown>" });

    {
        auto transaction = manager->transaction();
        auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
        driver->setLastName("Erickson");
        driver->update();
        transaction.commit();
    }

    auto driverClone = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");
    QCOMPARE(driverClone->getLastName(), QString{ "Erickson" });
}

void DatabaseSuite::init()
{
    adminCredentials            = make<Credentials>(Role::ADMIN, "LOGIN1", "PASSWORD1");
    admin                       = make<User>("Adminka", "<Unknown>", adminCredentials);

    auto driverCredentials1     = make<Credentials>(Role::DRIVER, "LOGIN2", "PASSWORD2");
    auto drivercredentials2     = make<Credentials>(Role::DRIVER, "LOGIN3", "PASSWORD4");
    auto driver1                = make<User>("Driver 1", "<Unknown>", driverCredentials1);
    auto driver2                = make<User>("Driver 2", "<Unknown>", drivercredentials2);

    manager->persist(adminCredentials);
    manager->persist(admin);
    manager->persist(driverCredentials1);
    manager->persist(driver1);
    manager->persist(drivercredentials2);
    manager->persist(driver2);
}

void DatabaseSuite::cleanup()
{
    manager->clearTable<User>();
    manager->clearTable<Credentials>();
}


static DatabaseSuite databaseSuite;

