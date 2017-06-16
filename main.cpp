#include <QCoreApplication>

#include "TransportEmpireApp.h"

#include "Test/TestSuite.h"

#include "Database/Database.h"
#include "Database/EntityManager.h"

#include "Model/User.h"

#include "Utility.h"


int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

//    TransportEmpireApp application;

#ifdef QT_DEBUG
    // Runs all unit tests instantiated as QTestSuite
    QTestSuite::RunAllTests(argc, argv);
#endif

    return app.exec();
}
