#include <QCoreApplication>

#include "TransportEmpireApp.h"

#include "Test/TestSuite.h"

#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Model/User.h"

#include "Utility.h"


void testDatabase()
{
    db::Database database{ "TransportEmpireDB" }; database.connect();
    db::EntityManager* manager = database.createManagerInstance();

    try {
        auto c = make<Credentials>(Role::ADMIN, "LOGIN2", "PASSWORD");
        manager->persist(c);
        manager->persist(make<User>("A", "B", c));
    } catch (std::exception& e) {
        qStdOut() << "Exception: " << e.what() << endl;
    }
}


int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

//    TransportEmpireApp application;

#ifdef QT_DEBUG
    // Runs all unit tests instantiated as QTestSuite
    QTestSuite::RunAllTests(argc, argv);
#endif

    testDatabase();

    return app.exec();
}
