#include "Test/Suites/DatabaseSuite.h"
#include "Model/User.h"
#include "Utility.h"

DatabaseSuite::DatabaseSuite()
    : database{ "TransportEmpireDB" },
      manager{ database.createManagerInstance() }
{
    database.connect();
}

void DatabaseSuite::entityManagerTest()
{
    Pointer<User> user{
        new User{
            "A", "B", Pointer<Credentials>{
                new Credentials{ Role::ADMIN, "LOGIN", "PASSWORD" }
            }
        }
    };
    manager->persist(user);
}

//static DatabaseSuite databaseSuite;
