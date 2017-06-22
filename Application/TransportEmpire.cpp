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

    display.dissableLaunchButton();
    display.setStatus("Status: Launching...");

    QFuture<void> launch = QtConcurrent::run([=] () {
        test(login, password);
        core.prepare(login, password);
    });
    core.launch();
}

}
 // namespace app
