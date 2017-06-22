#include "Application/Core.h"
#include "Server/ControllerSuite.h"
#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"
#include "Model/Credentials.h"
#include "Model/User.h"

#include "Utility.h"

namespace app {

Core::Core(QObject* parent)
    : QObject{ parent }
{
        qStdOut() << "Native thread: " << threadId() << endl;

        database.reset(new db::RemoteDatabase {
                "TransportEmpireDB",
                "sqlexpress2014.cvn90iitbqfj.us-west-2.rds.amazonaws.com",
                1433
        });

        auto suite = new srv::ControllerSuite{ database.data() };
        suite->add<srv::UserController>();
        suite->add<srv::RouteController>();

        server.reset(srv::Server::build()
                .name("Test Server")
                .address(QHostAddress::LocalHost)
                .port(8080)
                .controllerSuite(suite)
                .make()
        );

        connect(server.data(), &srv::Server::launched, this, &Core::serverLaunched);
        connect(server.data(), &srv::Server::terminated, this, &Core::serverTerminated);
        connect(server.data(), &srv::Server::failedToLaunch, this, &Core::serverFailedToLaunch);
}

void Core::launch()
{
    server->launchAsync();
}

void Core::terminate()
{
    server->terminate();
}

void Core::prepare(std::string login, std::string password)
{
    try {
        database->connect(login, password);
        auto manager = database->createManagerInstance();
        manager->startSession();

        manager->erase<User>();
        manager->erase<Credentials>();

        Pointer<Credentials> adminCredentials   = make<Credentials>(Role::ADMIN, "LOGIN", "PASSWORD");
        Pointer<User> admin                     = make<User>("Admin", "Admin", adminCredentials);

        manager->persist(adminCredentials);
        manager->persist(admin);
    } catch (...) {
        emit databasePreparationFailed(std::current_exception());
    }
}

} // namespace app
