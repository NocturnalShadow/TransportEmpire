#include <QDebug>
#include <QCoreApplication>

#include "Test/TestSuite.h"

#include "Server/WebServer.h"

#include "Database/Database.h"

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

#ifdef QT_DEBUG
	// Runs all unit tests instantiated as QTestSuite
	QTestSuite::RunAllTests(argc, argv);
#endif

//	WebServer server;
//	server.open(8080);

    db::DatabaseConnection db{ "TransportEmpireDB" };
    db.Connect();

	return app.exec();
}
