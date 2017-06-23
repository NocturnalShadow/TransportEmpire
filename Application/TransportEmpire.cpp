#include "Application/TransportEmpire.h"
#include "Test/TestSuite.h"
#include "Utility.h"

#include <QtConcurrent>

namespace app {

TransportEmpire::TransportEmpire(int argc, char* argv[])
    : application{ argc, argv }
{
    connect(&display, &Display::launchButtonClicked,
            this, &TransportEmpire::onLaunchButtonClicked);
    connect(&core, &Core::serverLaunched, [&] () {
            display.setStatus("Status: Server launched.");
    });
    connect(&core, &Core::serverTerminated, [&] () {
            display.enableLaunchButton();
    });
    connect(&core, &Core::serverFailedToLaunch, [&] () {
            display.setStatus("Status: Failed to launch server.");
            display.enableLaunchButton();
    });
    connect(&core, &Core::databasePreparationFailed, [&] () {
            display.setStatus("Status: Failed to prepare the database.");
            core.terminate();
    });
}

void TransportEmpire::test(std::string login, std::string password)
{
#ifdef QT_DEBUG
    QTestSuite::RunAllTests({ login, password });
#endif
}

void TransportEmpire::run()
{
    display.show();
    application.exec();
}

void TransportEmpire::onLaunchButtonClicked()
{
    std::string login       = display.getLogin().toStdString();
    std::string password    = display.getPassword().toStdString();
    std::string address     = display.getAddress().toStdString();
    unsigned int port       = display.getPort().toUInt();

    display.dissableLaunchButton();
    display.setStatus("Status: Launching...");

    core.initialize(address, port);
    core.launch();

    QFuture<void> launch = QtConcurrent::run([=] () {
        try {
            test(login, password);
        } catch (std::exception& e) {
            qStdOut() << "Exception: " << e.what() << endl;
        } catch(...) {

        }
        core.prepare(login, password);
    });

}

}
 // namespace app
