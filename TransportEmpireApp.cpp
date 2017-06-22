#include "TransportEmpireApp.h"

#include "Server/Server.h"
#include "Server/ControllerSuite.h"
#include "Server/Controllers/RouteController.h"
#include "Server/Controllers/UserController.h"
#include "Model/Credentials.h"
#include "Model/User.h"

#include "Utility.h"

TransportEmpireApp::TransportEmpireApp(QObject* parent)
    : QObject{ parent },
      database{ "TransportEmpireDB", "SQLEXPRESS" } // special for Karolina's pc
{
        qStdOut() << "Native thread: " << threadId() << endl;

        auto suite = new srv::ControllerSuite{ &database };
        suite->add<srv::UserController>();
        suite->add<srv::RouteController>();

        server = srv::Server::build()
                .name("Test Server")
                .address(QHostAddress::LocalHost)
                .port(8080)
                .controllerSuite(suite)
                .makeUnique();
}

void TransportEmpireApp::launch()
{
    server->launchAsync();
}

void TransportEmpireApp::init()
{
    database.connect();
    auto manager = database.createManagerInstance();
    manager->startSession();

    try {
        manager->erase<User>();
        manager->erase<Credentials>();
    } catch(std::exception& e) {
        qStdOut() << "Exception: " << e.what() <<endl;
    }

    Pointer<Credentials> adminCredentials   = make<Credentials>(Role::ADMIN, "LOGIN", "PASSWORD");
    Pointer<User> admin                     = make<User>("Admin", "Admin", adminCredentials);

    try {
        manager->persist(adminCredentials);
        manager->persist(admin);
    } catch(std::exception& e) {
        qStdOut() << "Exception: " << e.what() << endl;
    }
}
