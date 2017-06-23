#include "Test/Suites/DatabaseSuite.h"
#include "Database/Database.h"
#include "Database/EntityManager.h"
#include "Utility.h"

DatabaseSuite::DatabaseSuite()
{
//    database = new db::RemoteDatabase {
//            "TransportEmpireTDB",
//            "sqlexpress2014.cvn90iitbqfj.us-west-2.rds.amazonaws.com",
//            1433
//    };
     database = new db::LocalDatabase{ "TransportEmpireDB" };
}

void DatabaseSuite::initTestCase()
{
    database->connect(args[0], args[1]);
    manager = database->createManagerInstance();
    manager->startSession();
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
    // erase with transaction rollback
    auto query{ db::Query<User>::credentials->role == Role::DRIVER };
    {
        db::Transaction transaction{ manager };
        manager->erase<User>(query);
    } // <- rolling back the transactions
    auto drivers = manager->query<User>(query);
    QCOMPARE(drivers.size(), 2);

    // erase one
    {
        auto query{ db::Query<User>::firstName == "Driver 1" };
        auto driver = manager->queryOne<User>(query);
        driver->erase();
        driver = manager->queryOne<User>(query);
        QCOMPARE(driver.data(), nullptr);
    }

    // query erase
    {
        auto query{ db::Query<User>::credentials->role == Role::DRIVER };
        manager->erase<User>(query);
        auto drivers = manager->query<User>(query);
        QCOMPARE(drivers.size(), 0);
    }
}

void DatabaseSuite::transactionTest()
{
    auto driver = manager->queryOne<User>(db::Query<User>::firstName == "Driver 1");

    // manual transaction rollback
    {
        db::Transaction transaction{ manager };
        driver->setLastName("Erickson");
        driver->update();
        transaction.rollback();
        QCOMPARE(driver->getLastName(), QString{ "<Unknown>" });
    }

    // automatic transaction rollback
    {
        db::Transaction transaction{ manager };
        driver->setLastName("Erickson");
        driver->update();
    } // <- rolling back the transactions
    QCOMPARE(driver->getLastName(), QString{ "<Unknown>" });

    // transaction commit
    {
        db::Transaction transaction{ manager };
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
    auto drivercredentials2     = make<Credentials>(Role::DRIVER, "LOGIN3", "PASSWORD3");
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
    manager->erase<User>();
    manager->erase<Credentials>();
}


static DatabaseSuite databaseSuite;

