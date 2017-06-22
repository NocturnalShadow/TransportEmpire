#include <QCoreApplication>

#include "TransportEmpireApp.h"

#include "Test/TestSuite.h"
#include "Utility.h"


int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

#ifdef QT_DEBUG
    // Runs all unit tests instantiated as QTestSuite
    QTestSuite::RunAllTests(argc, argv);
#endif
    QTestSuite::RunAllTests(argc, argv);

    TransportEmpireApp application;
    application.init();


    application.launch();

    return app.exec();
}
