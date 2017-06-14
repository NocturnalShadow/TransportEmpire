#include <QCoreApplication>
#include <QThread>

#include "Test/TestSuite.h"

#include "Server/Server.h"
#include "Server/ControllerSuite.h"
#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"

#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Utility.h"


int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

#ifdef QT_DEBUG
	// Runs all unit tests instantiated as QTestSuite
	QTestSuite::RunAllTests(argc, argv);
#endif

    qStdOut() << "Native thread: " << QThread::currentThreadId() << endl;

    db::Database database{ "TransportEmpireDB" };
    database.connect();

    auto suite = new srv::ControllerSuite{ &database };
    suite->add<srv::UserController>();
    suite->add<srv::RouteController>();

    auto server = srv::Server::build()
            .name("Test Server")
            .address(QHostAddress::LocalHost)
            .port(8080)
            .controllerSuite(suite)
            .makeUnique();

    server->launchAsync();

    return app.exec();
}
